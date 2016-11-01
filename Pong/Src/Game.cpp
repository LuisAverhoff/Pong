#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Ball.h"
#include "Paddle.h"
#include "Graphics.h"
#include "Input.h"
#include "Sound.h"
#include "Timer.h"

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	playerScore = 0;
	AIScore = 0;
	running = true;
}

void Game::playGame()
{
	SDL_DisplayMode currentDisplaySize;
	SDL_GetCurrentDisplayMode(0, &currentDisplaySize);

	playerPaddle = (std::make_unique<Paddle>(20.0f, currentDisplaySize.h / 2.0f - 50.0f, 10, 100));
	AIPaddle = (std::make_unique<Paddle>(currentDisplaySize.w - 30.0f, currentDisplaySize.h / 2.0f - 50.0f, 10, 100));
	ball = (std::make_unique<Ball>(currentDisplaySize.w / 2.0f, currentDisplaySize.h / 2.0f, 13.0f));

	Graphics graphics(currentDisplaySize.w, currentDisplaySize.h);
	Input input;
	SDL_Event evt;
	Sound sound;
	Timer timer;

	while(running)
	{
		timer.setTicks();
		getEvent(input, evt, graphics);
	    updateObjects(graphics, sound, input, timer);
		renderObjects(graphics);
	}
} 

void Game::getEvent(Input &input, SDL_Event &evt, Graphics &graphics)
{
	input.resetKeys();

	if (SDL_PollEvent(&evt))
	{
		if (evt.type == SDL_KEYDOWN)
		{
			if (evt.key.repeat == 0)
			{
				input.keyPressedEvent(evt);
			}
		}
		else if (evt.type == SDL_KEYUP)
		{
			input.keyReleasedEvent(evt);
		}
		else if (evt.type == SDL_QUIT)
		{
			running = false;
		}
	}

	if (input.isKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		running = false;
	}

	if (input.isKeyPressed(SDL_SCANCODE_SPACE) && !ball->isBallLaunched())
	{
		ball->launchBall();
	}

	if (input.isKeyPressed(SDL_SCANCODE_F11))
	{
		int flags = SDL_GetWindowFlags(graphics.getWindowScreen());

		if (flags & SDL_WINDOW_FULLSCREEN)
		{
			SDL_SetWindowFullscreen(graphics.getWindowScreen(), 0);
		}
		else
			SDL_SetWindowFullscreen(graphics.getWindowScreen(), SDL_WINDOW_FULLSCREEN);
	}
}

void Game::updateObjects(Graphics &graphics, Sound &sound, Input input, Timer timer)
{
	float timeStep = timer.getTicks();

	if (ball->getVelocityX() > 0.0f)
	{
		AIPaddle->AIMove(ball.get(), timeStep, graphics.SCREEN_HEIGHT - 10); // SCREEN_HEIGHT - Height of the bottom rectangle.
	} 

	float playerPaddleNewYPos = playerPaddle->Y_VELOCITY * timeStep;

	if(input.isPaddleMovingUp())
	{
		playerPaddle->moveUp(playerPaddleNewYPos);
	}
	else if(input.isPaddleMovingDown())
	{
		playerPaddle->moveDown(playerPaddleNewYPos, graphics.SCREEN_HEIGHT - 10);
	}

	float ballNewXPos = ball->getVelocityX() * timeStep;
	float ballNewYPos = ball->getVelocityY() * timeStep;
	ball->move(ballNewXPos, ballNewYPos);

	ball->checkForCollision(timeStep, playerPaddle.get(), AIPaddle.get(), sound, graphics.SCREEN_WIDTH, graphics.SCREEN_HEIGHT - 10);

	ball->updateScore(&playerScore, &AIScore, sound, graphics.SCREEN_WIDTH, graphics.SCREEN_HEIGHT);
}

void Game::renderObjects(Graphics &graphics)
{
	graphics.drawToScreen(playerPaddle.get(), AIPaddle.get(), ball.get(), playerScore, AIScore);
}

void Game::quitGame()
{
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

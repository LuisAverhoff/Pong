#include "Game.h"
#include <SDL_ttf.h>
#include <string>

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
	ball = ((std::make_unique<Ball>(currentDisplaySize.w / 2.0f, currentDisplaySize.h / 2.0f, 13.0f)));

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

	if(input.isPaddleMovingUp())
	{
		playerPaddle->moveUp(timeStep);
	}
	else if(input.isPaddleMovingDown())
	{
		playerPaddle->moveDown(timeStep, graphics.SCREEN_HEIGHT - 10); // SCREEN_HEIGHT - Height of the bottom rectangle.
	}

	ball->move(timeStep);
	ball->checkForCollision(timeStep, playerPaddle.get(), AIPaddle.get(), sound, graphics.SCREEN_WIDTH, graphics.SCREEN_HEIGHT - 10);
	ball->updateScore(&playerScore, &AIScore, sound, graphics.SCREEN_WIDTH, graphics.SCREEN_HEIGHT);
}

void Game::renderObjects(Graphics &graphics)
{
	std::string playerScoreStr = std::to_string(playerScore);
	std::string AIScoreStr = std::to_string(AIScore);
	
	int xPlayerPos = (int)playerPaddle->PADDLE_X_POSITION;
	int yPlayerPos = (int)playerPaddle->getYPosition();

	int xAIPos = (int)AIPaddle->PADDLE_X_POSITION;
	int yAIPos = (int)AIPaddle->getYPosition();

	int playerPaddleWidth = playerPaddle->PADDLE_WIDTH;
	int playerPaddleHeight = playerPaddle->PADDLE_HEIGHT;

	int AIPaddleWidth = AIPaddle->PADDLE_WIDTH;
	int AIPaddleHeight = AIPaddle->PADDLE_HEIGHT;

	SDL_Rect playerRect = { xPlayerPos, yPlayerPos, playerPaddleWidth, playerPaddleHeight };
	SDL_Rect AIRect = { xAIPos, yAIPos, AIPaddleWidth, AIPaddleHeight };

	Sint16 ballCenterX = (Sint16)ball->getCenterX();
	Sint16 ballCenterY = (Sint16)ball->getCenterY();
	Sint16 ballRadius = (Sint16)ball->RADIUS;

	graphics.drawToScreen(&playerRect, &AIRect, ballCenterX, ballCenterY, ballRadius, playerScoreStr, AIScoreStr);
}

void Game::quitGame()
{
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}
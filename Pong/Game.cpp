/* Game.cpp for the Game Class
*
* Contains the main game loop that keeps the game running indefinitely, 
* drawing and redrawing any objects as they move their position and updating the
* FPS counter.
*/

#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Fps.h"
#include <SDL.h>

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	running = true;
	run();
	quitGame();
}

Game::~Game()
{
}

void Game::run()
{
	Graphics graphics;
	Fps fps;
	Input input;
	SDL_Event evt;

	while(running)
	{
		input.resetKeys();

		if(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_KEYDOWN)
			{
				if(evt.key.repeat == 0)
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

		if(input.isKeyPressed(SDL_SCANCODE_ESCAPE) == true)
		{
			running = false;
		}

		update(graphics, fps);
	}
}

void Game::update(Graphics &graphics, Fps &fps)
{
	graphics.drawToScreen();
	fps.updateFps();
}

void Game::quitGame()
{
	SDL_Quit();
}

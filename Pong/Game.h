/*Game Class
*
* Contains the main game loop that keeps the game running indefinitely and updates the objects on the screen as wells
* exiting the game once it is done.
*/

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Paddle.h"
#include "Ball.h"
#include "Input.h"
#include "Graphics.h"
#include "Sound.h"
#include "Timer.h"

class Game
{
	public:
		Game();
		void playGame();
		void quitGame();

	private:
		void getEvent(Input &, SDL_Event &, Graphics &);
		void updateObjects(Graphics &, Sound &, Input, Timer);
		void renderObjects(Graphics &);
	
	private:
		std::unique_ptr<Paddle> playerPaddle;
		std::unique_ptr<Paddle> AIPaddle;
		std::unique_ptr<Ball> ball;
		unsigned int playerScore;
		unsigned int AIScore;
		bool running;
};

#endif 

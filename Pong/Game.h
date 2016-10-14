#ifndef GAME_H
#define GAME_H

class Graphics;
class Fps;

class Game
{
	public:
		Game();
		~Game();

	private:
		void run();
		void update(Graphics &, Fps &);
		void quitGame();
		bool running;
};

#endif 

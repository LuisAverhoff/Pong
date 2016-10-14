/* Graphics Class
 *
 * initializes and deallocates each object that will be used for rendering and drawing to the screen.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

class Graphics
{
	public:
		Graphics();
		~Graphics();
		void drawToScreen();
		void flip();
		void clear();

	private:
		void createPaddles();
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Rect *playerPaddle;
		SDL_Rect *AIPaddle;
		SDL_Rect *ball;
};

#endif 

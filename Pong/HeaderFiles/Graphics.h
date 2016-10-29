/* Graphics Class
 *
 * initializes and deallocates each object that will be used for rendering and drawing to the screen.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <memory>
#include <string>
#include <SDL.h>

namespace SDL2Graphics
{
	struct SDL2Graphics_Deleter
	{
		void operator()(SDL_Renderer *ptr) const { SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window *ptr) const { SDL_DestroyWindow(ptr); }
		void operator()(SDL_Texture *ptr) const { SDL_DestroyTexture(ptr); }
	};

	using windowPtr = std::unique_ptr<SDL_Window, SDL2Graphics_Deleter>;
	using rendererPtr = std::unique_ptr<SDL_Renderer, SDL2Graphics_Deleter>;
	using texturePtr = std::unique_ptr<SDL_Texture, SDL2Graphics_Deleter>;
}

class Graphics
{
	public:
		Graphics(const int, const int);
		void drawToScreen(SDL_Rect *, SDL_Rect *, Sint16, Sint16, Sint16, std::string, std::string);
		SDL_Window *getWindowScreen();

	private:
		std::unique_ptr<SDL_Window, SDL2Graphics::SDL2Graphics_Deleter> createWindow(char const *, int, int, int, int, Uint32);
		std::unique_ptr<SDL_Renderer, SDL2Graphics::SDL2Graphics_Deleter> createRenderer(SDL_Window *, int, Uint32);
		std::unique_ptr<SDL_Texture, SDL2Graphics::SDL2Graphics_Deleter> createTextTexture(SDL_Surface *);
		SDL2Graphics::windowPtr window;
		SDL2Graphics::rendererPtr renderer;
		SDL2Graphics::texturePtr playerScoreTexture;
		SDL2Graphics::texturePtr AIScoreTexture;
	
	private:
		void drawScore(const char *, const char *);
		void drawVerticalLine();
		void drawHorizontalBoxes();

	public:
		const int SCREEN_WIDTH;
		const int SCREEN_HEIGHT;
};

#endif 

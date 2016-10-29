#include "Graphics.h"
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <string>

Graphics::Graphics(const int WIDTH, const int HEIGHT) : SCREEN_WIDTH(WIDTH), SCREEN_HEIGHT(HEIGHT)
{
	window = createWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  SCREEN_WIDTH, SCREEN_HEIGHT, 
		SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE);
	renderer = createRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED);
}

std::unique_ptr<SDL_Window, SDL2Graphics::SDL2Graphics_Deleter> 
Graphics::createWindow(char const *title, int x, int y, int w, int h, Uint32 flags)
{
	return std::unique_ptr<SDL_Window, SDL2Graphics::SDL2Graphics_Deleter>(SDL_CreateWindow(title, x, y, w, h, flags), SDL2Graphics::SDL2Graphics_Deleter());
}

std::unique_ptr<SDL_Renderer, SDL2Graphics::SDL2Graphics_Deleter>
Graphics::createRenderer(SDL_Window *window, int index, Uint32 flags)
{
	return std::unique_ptr<SDL_Renderer, SDL2Graphics::SDL2Graphics_Deleter>(SDL_CreateRenderer(window, index, flags), SDL2Graphics::SDL2Graphics_Deleter());
}

std::unique_ptr<SDL_Texture, SDL2Graphics::SDL2Graphics_Deleter>
Graphics::createTextTexture(SDL_Surface *textSurface)
{
	return std::unique_ptr<SDL_Texture, SDL2Graphics::SDL2Graphics_Deleter>
		(SDL_CreateTextureFromSurface(renderer.get(), textSurface), SDL2Graphics::SDL2Graphics_Deleter());
}

SDL_Window *Graphics::getWindowScreen()
{
	return window.get();
}

void Graphics::drawToScreen(SDL_Rect *playerRect, SDL_Rect *AIRect, Sint16 ballCenterX, Sint16 ballCenterY, 
								  Sint16 ballRadius, std::string playerScoreText, std::string AIScoreText)
{
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer.get());
	SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
	drawHorizontalBoxes();
	drawVerticalLine();
	drawScore(playerScoreText.c_str(), AIScoreText.c_str());
	SDL_RenderFillRect(renderer.get(), playerRect);
	SDL_RenderFillRect(renderer.get(), AIRect);
	filledCircleRGBA(renderer.get(), ballCenterX, ballCenterY, ballRadius, 255, 255, 255, 255);
	SDL_RenderPresent(renderer.get());
}

void Graphics::drawScore(const char *playerScoreText, const char *AIScoreText)
{
	TTF_Font *pixelFont = TTF_OpenFont("slkscr.ttf", 60);
	SDL_Color textColor = {255, 255, 255, 255};

	SDL_Surface *playerTextSurface = TTF_RenderText_Solid(pixelFont, playerScoreText, textColor);
	SDL_Surface *AiTextSurface = TTF_RenderText_Solid(pixelFont, AIScoreText, textColor);

	playerScoreTexture = createTextTexture(playerTextSurface);
	AIScoreTexture = createTextTexture(AiTextSurface);

	SDL_FreeSurface(playerTextSurface);
	SDL_FreeSurface(AiTextSurface);
	playerTextSurface = nullptr;
	AiTextSurface = nullptr;

	SDL_Rect playerTextRect;
	playerTextRect.x = (SCREEN_WIDTH / 2) - 52, playerTextRect.y = 20;
	SDL_QueryTexture(playerScoreTexture.get(), NULL, NULL, &playerTextRect.w, &playerTextRect.h);

	SDL_Rect AiTextRect;
	AiTextRect.x = (SCREEN_WIDTH / 2) + 10, AiTextRect.y = 20;
	SDL_QueryTexture(AIScoreTexture.get(), NULL, NULL, &AiTextRect.w, &AiTextRect.h);

	SDL_RenderCopy(renderer.get(), playerScoreTexture.get(), NULL, &playerTextRect);
	SDL_RenderCopy(renderer.get(), AIScoreTexture.get(), NULL, &AiTextRect);

	TTF_CloseFont(pixelFont);
}

void Graphics:: drawVerticalLine()
{
	int x = SCREEN_WIDTH / 2;
	int verticalMaxHeight = SCREEN_HEIGHT - 20;
	
	for (int y = 20; y < verticalMaxHeight; y += 6)
	{
		SDL_RenderDrawPoint(renderer.get(), x, y);
	}
}

void Graphics::drawHorizontalBoxes()
{
	SDL_Rect topHorizontalBox = {0, 0, SCREEN_WIDTH, 10};
	SDL_RenderFillRect(renderer.get(), &topHorizontalBox);

	SDL_Rect bottomHorizontalBox = { 0, SCREEN_HEIGHT - 10, SCREEN_WIDTH, 10};
	SDL_RenderFillRect(renderer.get(), &bottomHorizontalBox);
}
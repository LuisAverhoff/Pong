#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
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

void Graphics::drawToScreen(Paddle *playerPaddle, Paddle *AIPaddle, Ball *ball, unsigned int playerScore, unsigned int AIScore)
{
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer.get());
	SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
	drawHorizontalBoxes();
	drawVerticalLine();
	std::string playerScoreText = std::to_string(playerScore);
	std::string AIScoreText = std::to_string(AIScore);
	drawScore(playerScoreText.c_str(), AIScoreText.c_str());
	Sint16 playPaddleXPos1 = (Sint16)playerPaddle->PADDLE_X_POSITION;
	Sint16 playPaddleXPos2 = playPaddleXPos1 + playerPaddle->PADDLE_WIDTH;
	Sint16 playPaddleYPos1 = (Sint16)playerPaddle->getYPosition();
	Sint16 playPaddleYPos2 = playPaddleYPos1 + playerPaddle->PADDLE_HEIGHT;
	boxRGBA(renderer.get(), playPaddleXPos1, playPaddleYPos1, playPaddleXPos2, playPaddleYPos2, 255, 255, 255, 255);
	Sint16 AIPaddleXPos1 = (Sint16)AIPaddle->PADDLE_X_POSITION;
	Sint16 AIPaddleXPos2 = AIPaddleXPos1 + AIPaddle->PADDLE_WIDTH;
	Sint16 AIPaddleYPos1 = (Sint16)AIPaddle->getYPosition();
	Sint16 AIPaddleYPos2 = AIPaddleYPos1 + AIPaddle->PADDLE_HEIGHT;
	boxRGBA(renderer.get(), AIPaddleXPos1, AIPaddleYPos1, AIPaddleXPos2, AIPaddleYPos2, 255, 255, 255, 255);
	filledCircleRGBA(renderer.get(), (Sint16)ball->getCenterX(), (Sint16)ball->getCenterY(), (Sint16)ball->RADIUS, 255, 255, 255, 255);
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

	int playerTextWidth;

	TTF_SizeText(pixelFont, playerScoreText, &playerTextWidth, NULL);

	SDL_Rect playerTextRect;
	playerTextRect.x = (SCREEN_WIDTH / 2) - playerTextWidth - 5, playerTextRect.y = 20;
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

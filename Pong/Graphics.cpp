#include "Graphics.h"
#include <SDL.h>

const int PLAYER_PADDLE_POS_X = 20;
const int PLAYER_PADDLE_POS_Y = 190;
const int PLAYER_PADDLE_WIDTH = 10;
const int PLAYER_PADDLE_HEIGHT = 100;

const int AI_PADDLE_POS_X = 600;
const int AI_PADDLE_POS_Y = 190;
const int AI_PADDLE_WIDTH = 10;
const int AI_PADDLE_HEIGHT = 100;

const int BALL_POS_X = 310;
const int BALL_POS_Y = 230;
const int BALL_WIDTH = 20;
const int BALL_HEIGHT = 20;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Pong");
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	clear();
	flip();
	createPaddles();
}

void Graphics::createPaddles()
{
	playerPaddle = new SDL_Rect();
	playerPaddle->x = PLAYER_PADDLE_POS_X;
	playerPaddle->y = PLAYER_PADDLE_POS_Y;
	playerPaddle->w = PLAYER_PADDLE_WIDTH;
	playerPaddle->h = PLAYER_PADDLE_HEIGHT;

	AIPaddle = new SDL_Rect();
	AIPaddle->x = AI_PADDLE_POS_X;
	AIPaddle->y = AI_PADDLE_POS_Y;
	AIPaddle->w = AI_PADDLE_WIDTH;
	AIPaddle->h = AI_PADDLE_HEIGHT;

	ball = new SDL_Rect();
	ball->x = BALL_POS_X;
	ball->y = BALL_POS_Y;
	ball->w = BALL_WIDTH;
	ball->h = BALL_HEIGHT;
}

void Graphics::drawToScreen()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, playerPaddle);
	SDL_RenderFillRect(renderer, AIPaddle);
	SDL_RenderFillRect(renderer, ball);
	flip();
}

void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	window = nullptr;
	renderer = nullptr;

	delete playerPaddle;
	playerPaddle = nullptr;
	delete AIPaddle;
	AIPaddle = nullptr;
	delete ball;
	ball = nullptr;
}

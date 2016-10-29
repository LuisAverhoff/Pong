#include "Timer.h"

Timer::Timer(): currentTime(SDL_GetTicks())
{
	
}

void Timer::setTicks()
{
	oldTime = currentTime;
	currentTime = SDL_GetTicks();
	frameTime = (currentTime - oldTime) / 1000.0f;
}

float Timer::getTicks()
{
	return frameTime;
}

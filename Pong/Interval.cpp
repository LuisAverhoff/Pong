#include <SDL.h>
#include "Interval.h"

Interval::Interval() : initialInterval(SDL_GetTicks())
{
}

unsigned int Interval::getIntervalTime() const
{
	return SDL_GetTicks() - initialInterval;
}
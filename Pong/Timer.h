#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
	public:
		Timer();
		void setTicks();
		float getTicks();

	private:
		float frameTime;
		Uint32 oldTime, currentTime;
};

#endif


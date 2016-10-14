#ifndef FPS_H
#define FPS_H

#include "Interval.h"

class Fps
{
	public:
		Fps();
		void updateFps();
		unsigned int getFps() const;

	protected:
		unsigned int fps;
		unsigned int fpsCounter;
		Interval interval;
};

#endif


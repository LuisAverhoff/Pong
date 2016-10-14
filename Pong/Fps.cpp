#include "Fps.h"

Fps::Fps(): fps(0), fpsCounter(0)
{
	
}

void Fps::updateFps()
{
	fpsCounter++;

	// If more than one sec has passed.
	if(interval.getIntervalTime() > 1000)
	{
		fps = fpsCounter;
		fpsCounter = 0; // reset the counter
		interval = Interval(); // reset the interval
	}
}

unsigned int Fps::getFps() const
{
	return fps;
}

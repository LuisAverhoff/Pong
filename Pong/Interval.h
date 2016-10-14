/*Interval Class
 *
 * Used to calculate the delta time from the initial time to the time that we call the SDL_GetTicks function again.
 */

#ifndef INTERVAL_H
#define INTERVAL_H

class Interval
{
	public:
		Interval();
		unsigned int getIntervalTime() const;

	private:
		unsigned int initialInterval;
};

#endif


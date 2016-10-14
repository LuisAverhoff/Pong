/* Input Class
 *
 * Contains information on the state of all the keys in each map in relation to each event.
 */

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>

class Input
{
	public:
		void resetKeys();
		void keyPressedEvent(const SDL_Event &);
		void keyReleasedEvent(const SDL_Event &);
		bool isKeyPressed(SDL_Scancode);
		bool isKeyReleased(SDL_Scancode);
		bool isKeyHeld(SDL_Scancode);

	private:
		std::map<SDL_Scancode, bool> keysHeld;
		std::map<SDL_Scancode, bool> keysPressed;
		std::map<SDL_Scancode, bool> keysReleased;
};

#endif 


#include "Input.h"

// This function reset keys that are no longer relevant in the next frame.
void Input::resetKeys()
{
	keysPressed.clear();
	keysReleased.clear();
}

// This function gets called when a key is pressed down.
void Input::keyPressedEvent(const SDL_Event &evt)
{
	keysPressed[evt.key.keysym.scancode] = true;
	keysHeld[evt.key.keysym.scancode] = true;
}

// This function gets called when a key is released.
void Input::keyReleasedEvent(const SDL_Event &evt)
{
	keysReleased[evt.key.keysym.scancode] = true;
	keysHeld[evt.key.keysym.scancode] = false;
}

bool Input::isKeyPressed(SDL_Scancode key)
{
	return keysPressed[key];
}

bool Input::isKeyReleased(SDL_Scancode key)
{
	return keysReleased[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
	return keysHeld[key];
}


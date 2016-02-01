#include "input.h"

/* Input class
 * Keeps track of keyboard state
 */

//This Function gets called at each new frame to reset the keys
//that are no longer relevant.
void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

//this gets called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event) {
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

//gets called on key release
void Input::keyUpEvent(const SDL_Event& event) {
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
}

//check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->_releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key) {
	return this->_heldKeys[key];
}
#ifndef __INPUTMANAGER_HPP_
#define __INPUTMANAGER_HPP_

#include "menu.hpp"

class InputManager
{
private:
public:
	InputManager();
	~InputManager();
	void handleInput();
	void handleMenuInput(Menu &menu);
};

extern InputManager inputmgr;

#endif

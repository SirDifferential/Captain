#ifndef __INPUTMANAGER_HPP_
#define __INPUTMANAGER_HPP_

class InputManager
{
private:
public:
	InputManager();
	~InputManager();
	void handleInput();
	void handleMenuInput();
};

extern InputManager inputmgr;

#endif

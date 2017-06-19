#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Keyboard.h"

class InputManager
{
public:
	static void CreateInput();
	static Keyboard *GetInputKey();
	~InputManager();

private:
	static InputManager *instanceOf();
	static void managerCreate();
	InputManager();

	/* ----------------------------- DATA ------------------------------- */

	static InputManager *inputMan;
	Keyboard			*inputKey;

};
#endif // !INPUT_MANAGER_H

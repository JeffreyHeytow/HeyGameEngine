#include <assert.h>
#include "sb6.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{

}

bool Keyboard::getKeyState(INPUT_KEY thisKey)
{
	bool value;

	if(glfwGetKey(thisKey) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}
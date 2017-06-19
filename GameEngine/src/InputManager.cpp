#include <assert.h>
#include "InputManager.h"

InputManager *InputManager::inputMan = 0;

void InputManager::CreateInput()
{
	InputManager::managerCreate();
}

InputManager::InputManager()
{
	this->inputKey = new Keyboard();
	assert(this->inputKey);
}

void InputManager::managerCreate()
{
	InputManager::inputMan = new InputManager();
}

InputManager::~InputManager()
{
	delete this->inputKey;
}

Keyboard *InputManager::GetInputKey()
{
	InputManager *thisManager = InputManager::instanceOf();
	return thisManager->inputKey;
}

InputManager *InputManager::instanceOf()
{
	assert(inputMan);
	return inputMan;
}


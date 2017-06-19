#include <assert.h>
#include "Camera_Manager.h"
#include "Keyboard.h"
#include "InputManager.h"

Camera_Manager::Camera_Manager()
{
}

Camera_Manager * Camera_Manager::instanceOf(void)
{
	static Camera_Manager instance;
	return &instance;
}

void Camera_Manager::addCamera(Camera *thisCamera)
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();

	thisManager->managerAddCamera(thisCamera, thisManager->headNode);
}

void Camera_Manager::managerAddCamera(Camera_Node *thisNode, Camera_Node *&thisHead)
{
	assert(thisNode != 0);

	if(thisHead == 0)
	{
		thisHead = thisNode;
		thisNode->nextNode = 0;
		thisNode->prevNode = 0;
	}
	else
	{
		thisNode->nextNode = headNode;
		thisHead->prevNode = thisNode;
		thisHead = thisNode;
	}

}

Camera_Node * Camera_Manager::findCamera(CameraName thisCamera)
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	//search by name
	Camera_Node *thisActive = thisManager->activeCamera;

	while(thisActive != 0)
	{
		if(thisManager->activeCamera->getCameraName() == thisCamera)
		{
			//camera found
			break;
		}

		thisActive = thisActive->prevNode;
	}

	return (Camera *)thisActive;
}

void Camera_Manager::updateGameCamera()
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	assert(thisManager);

	Camera *thisCamera = 0;

	Camera_Node *thisHead = thisManager->activeCamera;

	while(thisHead != 0)
	{
		thisCamera = (Camera *)thisHead;
		thisCamera->updateCamera();

		thisHead = thisHead->nextNode;
	}

	thisManager->checkCamera();
}


Camera * Camera_Manager::getActiveCamera()
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	assert(thisManager);
	return thisManager->activeCamera;
}


void Camera_Manager::setCamera1(Camera *thisCamera)
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	assert(thisManager);
	thisManager->camera1 = thisCamera;
}

void Camera_Manager::setCamera2(Camera *thisCamera)
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	assert(thisManager);
	thisManager->camera2 = thisCamera;
}

void Camera_Manager::setCamera3(Camera *thisCamera)
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	assert(thisManager);
	thisManager->camera3 = thisCamera;
}


void Camera_Manager::setActiveCamera(Camera *thisCamera)
{
	Camera_Manager *thisManager = Camera_Manager::instanceOf();
	assert(thisManager);
	thisManager->activeCamera = thisCamera;
}

void Camera_Manager::checkCamera()
{
	Keyboard *thisKey = InputManager::GetInputKey();

	if(thisKey->getKeyState(INPUT_KEY::INPUT_1) == true)
	{
		
		this->activeCamera = this->camera1;
		this->setActiveCamera(this->activeCamera);
	}
	
	if(thisKey->getKeyState(INPUT_KEY::INPUT_2) == true)
	{
		this->activeCamera = this->camera2;
		this->setActiveCamera(this->activeCamera);
	}

	if(thisKey->getKeyState(INPUT_KEY::INPUT_3) == true)
	{
		this->activeCamera = this->camera3;
		this->setActiveCamera(this->activeCamera);
		
	}

	
}
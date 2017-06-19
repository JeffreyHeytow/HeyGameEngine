#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include "PCSTree.h"

//singleton
class GameObject_Manager
{
public:
	static void addObject(GameObject *thisObject);
	static void drawObject(void);
	static void updateObject(float currTime);

private:
	GameObject_Manager();
	static GameObject_Manager *instanceOf();
	PCSTree *treeRoot;
};

#endif // !GAME_OBJECT_MANAGER_H

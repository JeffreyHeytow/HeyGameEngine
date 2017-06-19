#include <assert.h>
#include "GameObject.h"
#include "GameObject_Manager.h"



GameObject_Manager::GameObject_Manager()
{
	this->treeRoot = new PCSTree();
	assert(this->treeRoot);

	PCSNode *rootNode = new PCSNode("Root_Node");
	assert(rootNode);

	//set it to be the root
	treeRoot->insert(rootNode, 0);
}

GameObject_Manager * GameObject_Manager::instanceOf( void )
{
	static GameObject_Manager instance;
	return &instance;
}

void GameObject_Manager::addObject(GameObject *thisObject)
{
	assert(thisObject != 0);
	
	GameObject_Manager *thisManager = GameObject_Manager::instanceOf();

	PCSNode *rootNode = thisManager->treeRoot->getRoot();

	thisManager->treeRoot->insert(thisObject, rootNode);
}

void GameObject_Manager::updateObject(float currTime)
{
	GameObject_Manager *thisManager = GameObject_Manager::instanceOf();
	assert(thisManager);

	PCSNode *rootNode = thisManager->treeRoot->getRoot();
	assert(rootNode);

	GameObject *thisObject = 0;
	PCSNode *thisNode = rootNode->getChild();

	while(thisNode != 0)
	{
		thisObject = (GameObject *)thisNode;
		thisObject->update(currTime);

		thisNode = thisNode->getSibling();
	}
}

void GameObject_Manager::drawObject()
{
	GameObject_Manager *thisManager = GameObject_Manager::instanceOf();
	assert(thisManager);

	PCSNode *rootNode = thisManager->treeRoot->getRoot();
	assert(rootNode);

	GameObject *thisObject = 0;
	GraphicObject *thisGraphicObject = 0;
	PCSNode *thisNode = rootNode->getChild();

	while(thisNode != 0)
	{
		thisObject = (GameObject *)thisNode;
		thisGraphicObject = thisObject->getGraphic();
		assert(thisGraphicObject);
		thisGraphicObject->RenderGraphic();

		thisNode = thisNode->getSibling();
	}
}




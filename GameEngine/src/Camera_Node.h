#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

class Camera_Node
{
public:
	Camera_Node()
	{
		this->nextNode = 0;
		this->prevNode = 0;
	}

	Camera_Node *nextNode;
	Camera_Node *prevNode;
};

#endif // ! CAMERA_NODE_H



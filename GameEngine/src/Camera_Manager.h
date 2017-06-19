#ifndef  CAMERA_MANAGER_H
#define  CAMERA_MANAGER_H

#include "Camera.h"
#include "Camera_Node.h"

//singleton

class Camera_Manager
{
public:
	static void addCamera(Camera *thisCamera);
	static Camera_Node * findCamera(CameraName thisCamera);
	static void updateGameCamera();
	static Camera * getActiveCamera();
	static void setActiveCamera(Camera *thisCamera);
	static void setCamera1(Camera *thisCamera);
	static void setCamera2(Camera *thisCamera);
	static void setCamera3(Camera *thisCamera);

private:
	Camera_Manager();
	void managerAddCamera(Camera_Node *thisNode, Camera_Node *&thisHead);
	void checkCamera();
	static Camera_Manager *instanceOf();
	Camera *activeCamera;
	Camera *camera1;
	Camera *camera2;
	Camera *camera3;
	Camera_Node *headNode;

};
#endif // ! CAMERA_MANAGER_H

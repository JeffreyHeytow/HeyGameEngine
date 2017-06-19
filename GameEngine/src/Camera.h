#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"
#include "Camera_Node.h"

enum CameraName
{
	Camera_01,
	Camera_02, 
	Camera_03, 
	Camera_NOT_INITIALIZED
};

class Camera : public Camera_Node
{
public:
	Camera(CameraName thisCamera);

	//setup one camera:
	void setCameraPerspective(const float fieldOfView, const float aspectRatio, const float nearDistance, const float farDistance);
	void setCameraViewport(const int thisX, const int thisY, const int thisW, const int thisH);
	void setCameraOrientation(const Vect &thisUp, const Vect &thisLookAt, const Vect &thisPosition);

	//update the camera system
	void updateCamera(void);

	//get the matrices for rendering
	Matrix &getViewMatrix();
	Matrix &getProjMatrix();

	//helper methods
	CameraName getCameraName() const;

	void getCameraPosition( Vect &outPosition) const;
	void setCameraPosition( const Vect &inPosition);
	void getFieldOfView(float &thisFOV) const;
	void setFieldOfView(const float thisFOV);
	void getNearDistance(float &thisDist) const;
	void setNearDistance(const float thisDist);

	void getNearTopLeft(Vect &outVect) const;
	void getNearTopRight(Vect &outVect) const;
	void getNearBottomLeft(Vect &outVect) const;
	void getNearBottomRight(Vect &outvect) const;
	void getFarTopLeft(Vect &outVect) const;
	void getFarTopRight(Vect &outVect) const;
	void getFarBottomLeft(Vect &outVect) const;
	void getFarBottomRight(Vect &outVect) const;

	bool getStatus();
	void setStatus(bool status);
	
private:
	void setViewportState(void);
	void calculatePlaneDimensions(void);
	void calculateFrustrumVerts(void);
	void calculateFrustrumCollisionNorms(void);
	void updateProjectionMatrix(void);
	void updateViewMatrix(void);

	/* ----------------------------- DATA ------------------------------- */

	CameraName camera;

	//unit vectors 
	Vect upVector;
	Vect dirVector;
	Vect rightVector;  //derived from up and dir
	Vect posVector;

	//frustum inputs
	float nearDistance;
	float farDistance;
	float fieldOfView;
	float aspectRatio;

	//world space screen size
	float near_W;
	float near_H;
	float far_W;
	float far_H;

	//viewports
	int viewport_X;
	int viewport_Y;
	int viewport_W;
	int viewport_H;

	bool isActive;


	//frustrum coords in world space
	Vect nearTopLeft;
	Vect nearTopRight;
	Vect nearBottomLeft;
	Vect nearBottomRight;
	Vect farTopLeft;
	Vect farTopRight;
	Vect farBottomLeft;
	Vect farBottomRight;

	//frustrum normalization
	Vect frontNorm;
	Vect backNorm;
	Vect rightNorm;
	Vect leftNorm;
	Vect topNorm;
	Vect bottomNorm;

	//projection matrix
	Matrix projectionMatrix;
	Matrix viewportMatrix;
};
#endif // !CAMERA_H

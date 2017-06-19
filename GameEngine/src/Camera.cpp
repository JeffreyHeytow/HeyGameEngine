#include <assert.h>
#include "sb6.h"
#include <math.h>
#include "Camera.h"
#include "Keyboard.h"
#include "InputManager.h"

Camera::Camera(CameraName thisCamera)
{ 
	this->camera = thisCamera;
	this->isActive = false;
}

//from openGL - field of view Y is in degerees
/* informational knobs for controlling the perspective matrix */
void Camera::setCameraPerspective(const float fov_y, const float aspect, const float nearDist, const float farDist)
{
	this->aspectRatio = aspect;
	this->fieldOfView = fov_y;
	this->nearDistance = nearDist;
	this->farDistance = farDist;
}

void Camera::setCameraViewport(const int this_x, const int this_y, const int this_w, const int this_h)
{
	this->viewport_X = this_x;
	this->viewport_Y = this_y;
	this->viewport_W = this_w;
	this->viewport_H = this_h;

	this->setViewportState();
}

void Camera::setViewportState(void)
{
	glViewport(this->viewport_X, this->viewport_Y, this->viewport_W, this->viewport_H);
}

/* calculater height and width for near and plane */
void Camera::calculatePlaneDimensions(void)
{
	this->near_H = 2.0f * tan((this->fieldOfView * MATH_PI/180.0f) * 0.5f) * this->nearDistance;
	this->near_W = this->near_H * this->aspectRatio;

	this->far_H = 2.0f * tan((this->fieldOfView * MATH_PI/180.0f) * 0.5f) * this->farDistance;
	this->far_W = this->far_H * this->aspectRatio;
}

void Camera::setCameraOrientation(const Vect &thisUp, const Vect &thisLookAt, const Vect &atPosition)
{
	// up, lookAt, and right are all perpendicular
	// prioritize lookAt, find right vect, correct up to make perpendicular
	// make sure all vectors are unit vectors

	//point running from screen to user
	this->dirVector = atPosition - thisLookAt;
	this->dirVector.norm();

	//clean up the vectors
	this->rightVector = thisUp.cross(this->dirVector);
	this->rightVector.norm();

	this->upVector = this->dirVector.cross(this->rightVector);
	this->upVector.norm();

	this->posVector = atPosition;
}

void Camera::calculateFrustrumVerts(void)
{
	this->nearTopLeft		= this->posVector - this->dirVector * this->nearDistance + this->upVector * this->near_H * 0.5f - this->rightVector * this->near_W * 0.5f;
	this->nearTopRight		= this->posVector - this->dirVector * this->nearDistance + this->upVector * this->near_H * 0.5f + this->rightVector * this->near_W * 0.5f;
	this->nearBottomLeft	= this->posVector - this->dirVector * this->nearDistance - this->upVector * this->near_H * 0.5f - this->rightVector * this->near_W * 0.5f;
	this->nearBottomRight	= this->posVector - this->dirVector * this->nearDistance - this->upVector * this->near_H * 0.5f + this->rightVector * this->near_W * 0.5f;

	this->farTopLeft		= this->posVector - this->dirVector * this->farDistance  + this->upVector * this->far_H  * 0.5f - this->rightVector * this->far_W  * 0.5f;
	this->farTopRight		= this->posVector - this->dirVector * this->farDistance  + this->upVector * this->far_H  * 0.5f + this->rightVector * this->far_W  * 0.5f;
	this->farBottomLeft		= this->posVector - this->dirVector * this->farDistance  - this->upVector * this->far_H  * 0.5f - this->rightVector * this->far_W  * 0.5f;
	this->farBottomRight	= this->posVector - this->dirVector * this->farDistance  - this->upVector * this->far_H  * 0.5f + this->rightVector * this->far_W  * 0.5f;
}

void Camera::calculateFrustrumCollisionNorms(void)
{
	//frustum normals around nearTopLeft
	Vect tempA = this->nearBottomLeft - this->nearTopLeft;
	Vect tempB = this->nearTopRight - this->nearTopLeft;
	Vect tempC = this->farTopLeft - this->nearTopLeft;

	this->frontNorm = tempA.cross(tempB);
	this->frontNorm.norm();

	this->leftNorm = tempC.cross(tempA);
	this->leftNorm.norm();

	this->topNorm = tempB.cross(tempC);
	this->topNorm.norm();

	//frustrum normals around farBottomRight
	tempA = this->farBottomLeft - this->farBottomRight;
	tempB = this->farTopRight - this->farBottomRight;
	tempC = this->nearBottomRight - this->farBottomRight;

	this->backNorm = tempA.cross(tempB);
	this->backNorm.norm();

	this->rightNorm = tempB.cross(tempC);
	this->rightNorm.norm();

	this->bottomNorm = tempC.cross(tempA);
	this->bottomNorm.norm();
}

void Camera::updateProjectionMatrix(void)
{
	this->projectionMatrix[m0] = 2.0f * this->nearDistance / this->near_W ;
	this->projectionMatrix[m1] = 0.0f;
	this->projectionMatrix[m2] = 0.0f;
	this->projectionMatrix[m3] = 0.0f;

	this->projectionMatrix[m4] = 0.0f;
	this->projectionMatrix[m5] = 2.0f * this->nearDistance / this->near_H;
	this->projectionMatrix[m6] = 0.0f;
	this->projectionMatrix[m7] = 0.0f;

	this->projectionMatrix[m8] = 0.0f;
	this->projectionMatrix[m9] = 0.0f;
	this->projectionMatrix[m10] = (this->farDistance + this->nearDistance) / (this->nearDistance - this->farDistance);
	this->projectionMatrix[m11] = -1.0f;

	this->projectionMatrix[m12] = 0.0f;
	this->projectionMatrix[m13] = 0.0f;
	this->projectionMatrix[m14] = (2.0f * this->farDistance * this->nearDistance) / (this->nearDistance - this->farDistance);
	this->projectionMatrix[m15] = 0.0f;
}

void Camera::updateViewMatrix(void)
{
	this->viewportMatrix[m0] = this->rightVector[x];
	this->viewportMatrix[m1] = this->upVector[x];
	this->viewportMatrix[m2] = this->dirVector[x];
	this->viewportMatrix[m3] = 0.0f;
		  	  
	this->viewportMatrix[m4] = this->rightVector[y];
	this->viewportMatrix[m5] = this->upVector[y];
	this->viewportMatrix[m6] = this->dirVector[y];
	this->viewportMatrix[m7] = 0.0f;
		  	  
	this->viewportMatrix[m8] = this->rightVector[z];
	this->viewportMatrix[m9] = this->upVector[z];
	this->viewportMatrix[m10] = this->dirVector[z];
	this->viewportMatrix[m11] = 0.0f;
		  	  
	this->viewportMatrix[m12] = -posVector.dot(rightVector);
	this->viewportMatrix[m13] = -posVector.dot(upVector);
	this->viewportMatrix[m14] = -posVector.dot(dirVector);
	this->viewportMatrix[m15] = 1.0f;
}

/* update everything at one time */
void Camera::updateCamera(void)
{
	this->calculatePlaneDimensions();
	this->calculateFrustrumVerts();
	this->calculateFrustrumCollisionNorms();
	this->updateProjectionMatrix();
	this->updateViewMatrix();

	Keyboard *thisKey = InputManager::GetInputKey();


	if(thisKey->getKeyState(INPUT_KEY::INPUT_Z) == true)
	{
		Vect tempVect;
		this->getCameraPosition(tempVect);
		tempVect[z] -= 0.003f;
		this->setCameraPosition(tempVect);
	}
	
	if(thisKey->getKeyState(INPUT_KEY::INPUT_X) == true)
	{
		Vect tempVect;
		this->getCameraPosition(tempVect);
		tempVect[z] += 0.003f;
		this->setCameraPosition(tempVect);
	}
	
	if(thisKey->getKeyState(INPUT_KEY::INPUT_ARROW_UP) == true)
	{
		Vect tempVect;
		this->getCameraPosition(tempVect);
		tempVect[y] += 0.003f;
		this->setCameraPosition(tempVect);
	}

	if(thisKey->getKeyState(INPUT_KEY::INPUT_ARROW_DOWN) == true)
	{
		Vect tempVect;
		this->getCameraPosition(tempVect);
		tempVect[y] -= 0.003f;
		this->setCameraPosition(tempVect);
	}

	if(thisKey->getKeyState(INPUT_KEY::INPUT_ARROW_RIGHT) == true)
	{
		Vect tempVect;
		this->getCameraPosition(tempVect);
		tempVect[x] -= 0.003f;
		this->setCameraPosition(tempVect);
	}

	if(thisKey->getKeyState(INPUT_KEY::INPUT_ARROW_LEFT) == true)
	{
		Vect tempVect;
		this->getCameraPosition(tempVect);
		tempVect[x] += 0.003f;
		this->setCameraPosition(tempVect);
	}
}

//helper methods (accessors)
Matrix & Camera::getViewMatrix(void)
{
	return this->viewportMatrix;
}

Matrix & Camera::getProjMatrix(void)
{
	return this->projectionMatrix;
}

void Camera::getCameraPosition(Vect &retVect) const
{
	retVect = this->posVector;
}

void Camera::setCameraPosition(const Vect &thisVect)
{
	this->posVector = thisVect;
}

void Camera::getFieldOfView(float &thisFov) const
{
	thisFov = this->aspectRatio;
}

void Camera::setFieldOfView(const float thisFov)
{
	this->aspectRatio = thisFov;
}

void Camera::getNearDistance(float &thisDist) const
{
	thisDist = this->nearDistance;
}

void Camera::setNearDistance(const float thisDist)
{
	this->nearDistance = thisDist;
}

void Camera::getNearTopLeft(Vect &retVect) const
{
	retVect = this->nearTopLeft;
}

void Camera::getNearTopRight(Vect &retVect) const
{
	retVect = this->nearTopRight;
}

void Camera::getNearBottomLeft(Vect &retVect) const
{
	retVect = this->nearBottomLeft;
}

void Camera::getNearBottomRight(Vect &retVect) const
{
	retVect = this->nearBottomRight;
}

void Camera::getFarTopLeft(Vect &retVect) const
{
	retVect = this->farTopLeft;
}

void Camera::getFarTopRight(Vect &retVect) const
{
	retVect = this->farTopRight;
}

void Camera::getFarBottomLeft(Vect &retVect) const
{
	retVect = this->farBottomLeft;
}

void Camera::getFarBottomRight(Vect &retVect) const
{
	retVect = this->farBottomRight;
}

CameraName Camera::getCameraName() const
{
	return this->camera;
}

bool Camera::getStatus()
{
	return this->isActive;
}

void Camera::setStatus(bool status)
{
	this->isActive = status;
}


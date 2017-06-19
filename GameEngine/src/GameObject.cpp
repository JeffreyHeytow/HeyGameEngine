#include <assert.h>
#include <math.h>
#include "MathEngine.h"
#include "GameObject_Manager.h"
#include "GameObject.h"
#include "GraphicObject.h"
#include "PCSNode.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "GraphicTexture.h"
#include "TextureManager.h"


GameObject::GameObject(GraphicObject *thisGraphic)
	: PCSNode(), woldMatrix(IDENTITY), worldGraphic(thisGraphic),
	rot_Y(0.0f), rot_Z(0.0f), rotDelta(0.0f), rotZ(0.0f), rotX(0.0f),
	transVect(0.0f, 0.0f, 0.0f), scaleVect(1.0f, 1.0f, 1.0f)
{
	assert(thisGraphic != 0);
}

GraphicObject *GameObject::getGraphic()
{
	return this->worldGraphic;
}

void GameObject::setObjectPosition(const Vect &thisPosition)
{
	this->transVect = thisPosition;
}

void GameObject::setObjectScale(const Vect &thisScale)
{
	this->scaleVect = thisScale;
}

Matrix &GameObject::getWorld()
{
	return this->woldMatrix;
}

void GameObject::update(float currentTime)
{
	currentTime;
	this->rot_Y += rotDelta;
	this->rot_Z += rotZ;



	Matrix Scale(SCALE, this->scaleVect[x], this->scaleVect[y], this->scaleVect[z]);
	Matrix TransA( TRANS, this->transVect[x], this->transVect[y], this->transVect[z]);
	Matrix RotY(ROT_Y, this->rot_Y);
	Matrix RotZ(ROT_Z, this->rot_Z);
	
		
	this->woldMatrix = Scale * RotY * RotZ* TransA;
	this->worldGraphic->setWorldMatrix(this->woldMatrix);

	//push to graphics object
	this->worldGraphic->setWorldMatrix(this->woldMatrix);

	this->checkTextures();

}

void GameObject::checkTextures()
{
		Keyboard *thisKey = InputManager::GetInputKey();
		GraphicTexture *thisTexture = (GraphicTexture *)this->getGraphic();


	if(thisKey->getKeyState(INPUT_KEY::INPUT_M) == true)
	{
		thisTexture->textureName = TextureName::ME;
	}
	
	if(thisKey->getKeyState(INPUT_KEY::INPUT_D) == true)
	{
		thisTexture->textureName = TextureName::DOT_COM;
	}

	if(thisKey->getKeyState(INPUT_KEY::INPUT_B) == true)
	{
		thisTexture->textureName = TextureName::BRICK;
	}

		if(thisKey->getKeyState(INPUT_KEY::INPUT_S) == true)
	{
		thisTexture->textureName = TextureName::SHIP;
	}

}
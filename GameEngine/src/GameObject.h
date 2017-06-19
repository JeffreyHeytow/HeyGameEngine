#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "GameModel.h"
#include "GraphicObject.h"
#include "PCSNode.h"

class GameObject : public PCSNode
{
public:
	GameObject(GraphicObject *thisGraphic);

	void update(float time);
	Matrix &getWorld();

	void setGameModel(GameModel *thisModel);
	GraphicObject *getGraphic();
	
	void setObjectPosition(const Vect &thisPosition);
	void setObjectScale(const Vect &thisScale);
	float rotDelta;
	float rotZ;
	float rotX;


private:
	GameObject();
	GameObject(GraphicObject &copyGraphic);
	void checkTextures();

	/* ----------------------------- DATA ------------------------------- */

	Matrix woldMatrix;
	Vect transVect;
	Vect scaleVect;

	GraphicObject *worldGraphic;

	float rot_Y;
	float rot_Z;
	float rot_x;


};

#endif


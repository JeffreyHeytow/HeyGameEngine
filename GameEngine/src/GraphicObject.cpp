
#include <assert.h>
#include "GraphicObject.h"
#include "MathEngine.h"
#include "GameModel.h"

GraphicObject::GraphicObject(GameModel * thisModel, ProcessGraphic *toProcess)
	: graphicModel(thisModel), graphicProcess(toProcess)
{
	this->worldMatrix.set(IDENTITY);
	assert(thisModel);
	assert(toProcess);
}

GameModel *GraphicObject::getModel() const
{
	return this->graphicModel;
}

ProcessGraphic *GraphicObject::getRender() const
{
	return this->graphicProcess;
}

Matrix &GraphicObject::getWorldMatrix()
{
	return this->worldMatrix;
}

void GraphicObject::setWorldMatrix(Matrix &thisMatrix)
{
	this->worldMatrix = thisMatrix;
}
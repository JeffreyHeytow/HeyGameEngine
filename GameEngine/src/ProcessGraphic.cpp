#include <assert.h>
#include "GraphicObject.h"
#include "ProcessGraphic.h"

ProcessGraphic::ProcessGraphic(ShaderObject *thisShader)
	: renderShader(thisShader)
{
	assert(thisShader != 0);
}

void ProcessGraphic::ProcessGame(GraphicObject *thisGraphic)
{
	this->GameState(thisGraphic);
	this->DrawGame(thisGraphic);
}
#include <assert.h>

#include "GraphicLighting.h"
#include "ProcessGraphic.h"

GraphicLighting::GraphicLighting(GameModel *thisModel, ProcessGraphic *toRender, TextureName thisName, Vect &thisColor, Vect &thisPosition)
	: GraphicObject(thisModel, toRender), lightName(thisName), lightColor(thisColor), lightPosition(thisPosition)
{

}

void GraphicLighting::RenderGraphic()
{
	graphicProcess->ProcessGame(this);
}
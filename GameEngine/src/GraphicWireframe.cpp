#include <assert.h>

#include "GraphicWireframe.h"
#include "ProcessGraphic.h"

GraphicWireframe::GraphicWireframe(GameModel *thisModel, ProcessGraphic *toProcess)
	:GraphicObject(thisModel, toProcess)
{

}

void GraphicWireframe::RenderGraphic()
{
	graphicProcess->ProcessGame(this);
}
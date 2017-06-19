#include <assert.h>
#include "GraphicColorByPosition.h"
#include "ProcessGraphic.h"

GraphicColorByPosition::GraphicColorByPosition(GameModel *thisModel, ProcessGraphic *toProcess)
	: GraphicObject(thisModel, toProcess)
{

}

void GraphicColorByPosition::RenderGraphic()
{
	graphicProcess->ProcessGame(this);
}
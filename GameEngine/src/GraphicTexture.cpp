#include <assert.h>

#include "GraphicTexture.h"
#include "ProcessGraphic.h"
#include "Keyboard.h"
#include "InputManager.h"

GraphicTexture::GraphicTexture(GameModel *thisModel, ProcessGraphic *toRender,  TextureName thisTexture)
	: GraphicObject(thisModel, toRender), textureName(thisTexture)
{
}

void GraphicTexture::RenderGraphic()
{
	graphicProcess->ProcessGame(this);
}
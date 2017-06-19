#ifndef GRAPHIC_TEXTURE_H
#define GRAPHIC_TEXTURE_H

#include <sb6.h>
#include "GraphicObject.h"
#include "TextureNode.h"

class GraphicTexture : public GraphicObject
{

public:
	GraphicTexture(GameModel *thisModel, ProcessGraphic *toRender, TextureName thisTexture);
	virtual void RenderGraphic() override;

	/* ----------------------------- DATA ------------------------------- */
	TextureName textureName;

};

#endif // !GRAPHIC_TEXTURE_H

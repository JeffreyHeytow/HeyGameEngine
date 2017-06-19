#ifndef GRAPHIC_LIGHTING_H
#define GRAOHIC_LIGHTING_H

#include <sb6.h>
#include "GraphicObject.h"
#include "TextureNode.h"

class GraphicLighting : public GraphicObject
{
public:
	GraphicLighting(GameModel *thisModel, ProcessGraphic *toRender, TextureName thisName, Vect &thisColor, Vect &thisPosition);
	virtual void RenderGraphic() override;

	/* ----------------------------- DATA ------------------------------- */

	//GLuint TextID
	TextureName lightName;
	Vect lightColor;
	Vect lightPosition;
};

#endif // !GRAPHIC_LIGHTING_H

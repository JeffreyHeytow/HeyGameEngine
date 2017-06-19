#ifndef GRAPHIC_WIREFRAME_H
#define GRAPHIC_WIREFRAME_H

#include "GraphicObject.h"

class GraphicWireframe : public GraphicObject
{
public:
	GraphicWireframe(GameModel *thisModel, ProcessGraphic *toRender);
	virtual void RenderGraphic() override;

	/* ----------------------------- DATA ------------------------------- */

};

#endif // !GRAPHIC_WIREFRAME_H

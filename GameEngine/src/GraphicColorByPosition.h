#ifndef GRAPHIC_COLOR_BY_POSITION_H
#define GRAPHIC_COLOR_BY_POSITION_H

#include "GraphicObject.h"

class GraphicColorByPosition : public GraphicObject
{
public:
	GraphicColorByPosition(GameModel *thisModel, ProcessGraphic *toProcess);

	virtual void RenderGraphic() override;

	/* ----------------------------- DATA ------------------------------- */
	
	//uniform instancing stuff goes here...

};

#endif // !GRAPHIC_COLOR_BY_POSITION_H

#ifndef PROCESS_GRAPHIC_BY_POSITION_H
#define PROCESS_GRAPHIC_BY_POSITION_H

#include "GameObject.h"
#include "ProcessGraphic.h"
#include "ShaderObject.h"

class ProcessGraphic_ByPosition : public ProcessGraphic
{
public:
	ProcessGraphic_ByPosition(ShaderObject *thisShader);

private:
	void GameState(GraphicObject *thisObject) override;
	void DrawGame(GraphicObject *thisObject) override;

	GraphicType type;
};
#endif // !PROCESS_GRAPHIC_BY_POSITION_H

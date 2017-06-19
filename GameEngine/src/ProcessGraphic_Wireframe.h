#ifndef PROCESS_GRAPHIC_WIREFRAME_H
#define PROCESS_GRAPHIC_WIREFRAME_H

#include "GameObject.h"
#include "ProcessGraphic.h"
#include "ShaderObject.h"

class ProcessGraphic_Wireframe : public ProcessGraphic
{
public:
	ProcessGraphic_Wireframe(ShaderObject *thisShader);

private:
	void GameState(GraphicObject *thisObject) override;
	void DrawGame(GraphicObject *thisObject) override;

	/* ----------------------------- DATA ------------------------------- */

	GraphicType type;
};
#endif // !PROCESS_GRAPHIC_WIREFRAME_H

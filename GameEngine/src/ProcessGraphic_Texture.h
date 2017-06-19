#ifndef PROCESS_GRAPHIC_TEXTURE_H
#define PROCESS_GRAPHIC_TEXTURE_H

#include "GameObject.h"
#include "ProcessGraphic.h"
#include "ShaderObject.h"

class ProcessGraphic_Texture : public ProcessGraphic
{

public:
	ProcessGraphic_Texture(ShaderObject *thisShader);

private:
	void GameState(GraphicObject *thisObject) override;
	void DrawGame(GraphicObject *thisObject) override;

	/* ----------------------------- DATA ------------------------------- */

	GraphicType type;
};
#endif // !PROCESS_GRAPHIC_TEXTURE_H

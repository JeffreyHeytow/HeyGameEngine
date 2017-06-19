#ifndef GAME_TRANSLATION_H
#define GAME_TRANSLATION_H

#include "GameObject.h"
#include "ShaderObject.h"

class ProcessGraphic
{
public:

	enum class GraphicType
	{
		ColorByPosition,
		WireFrame,
		FlatTexture,
		TextureLighting,
	};

	ProcessGraphic(ShaderObject *thisShader);

	void ProcessGame(GraphicObject *thisGraphic);

	virtual void GameState(GraphicObject *thisObject) = 0;
	virtual void DrawGame(GraphicObject *thisObject) = 0;

	/* ----------------------------- DATA ------------------------------- */

	ShaderObject *renderShader;

};

#endif
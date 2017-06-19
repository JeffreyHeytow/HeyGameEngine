#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

#include "MathEngine.h"

class GameModel;
class ProcessGraphic;

class GraphicObject
{
public:

	GraphicObject(GameModel *thisModel, ProcessGraphic *toProcess);

	GameModel *getModel() const;
	ProcessGraphic *getRender() const;

	Matrix &getWorldMatrix();
	void setWorldMatrix(Matrix & thisMatrix);

	virtual void RenderGraphic() = 0;

	/* ----------------------------- DATA ------------------------------- */

protected:
	GameModel *graphicModel;
	ProcessGraphic *graphicProcess;
	Matrix worldMatrix;
};

#endif

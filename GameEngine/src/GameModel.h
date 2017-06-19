#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "MathEngine.h"
#include "sb6.h"

class GameModel
{
public:
	GameModel();
	virtual ~GameModel();

	/* ----------------------------- DATA ------------------------------- */

	int vertCount;
	int trisCount;

	GLuint vao;
	GLuint vbo[2];

private:

	virtual void generateVAO(const char* const thisVAOFile) = 0;
	//prevent from copying
	GameModel(GameModel &modelCopy);
	GameModel & operator = (GameModel &modelCopy);

};

#endif

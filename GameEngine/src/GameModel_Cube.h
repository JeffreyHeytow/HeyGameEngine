#ifndef GAMEMODEL_CUBE_H
#define GAMEMODEL_CUBE_H

#include "GameModel.h"

class GameModel_Cube : public GameModel
{
public:

	GameModel_Cube(const char* const cubeModelName);
	~GameModel_Cube();

private:
	void generateVAO(const char* const vaoFileName) override;

	/* ----------------------------- DATA ------------------------------- */

};

#endif // !GAME_H

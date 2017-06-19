#ifndef GAMEMODEL_STAR_H
#define GAMEMODEL_STAR_H

#include "GameModel.h"

class GameModel_Star : public GameModel
{
public:

	GameModel_Star(const char* const starModelName);
	~GameModel_Star();

private:
	void generateVAO(const char* const vaoFileName) override;

	/* ----------------------------- DATA ------------------------------- */
};

#endif // !GAMEMODEL_STAR_H

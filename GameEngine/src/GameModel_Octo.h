
#ifndef  GAMEMODEL_OCTO_H
#define GAMEMODEL_OCTO_H

#include "GameModel.h"

class GameModel_Octo : public GameModel
{
public:

	GameModel_Octo(const char* const starModelName);
	~GameModel_Octo();

private:
	void generateVAO(const char* const vaoFileName) override;

	/* ----------------------------- DATA ------------------------------- */
};

#endif // ! GAMEMODEL_OCTO_H
#ifndef GAMEMODEL_PYRAMID_H
#define GAMEMODEL_PYRAMID_H

#include "GameModel.h"

class GameModel_Pyramid : public GameModel
{
public:
	GameModel_Pyramid(const char* const pyramidModelName);
	~GameModel_Pyramid();

private:
	void generateVAO(const char* const vaoFileName) override;
};

#endif // !GAMEMODEL_PYRAMID_H

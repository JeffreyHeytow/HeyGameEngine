
#include "GameModel.h"

GameModel::GameModel()
	: vertCount(0), trisCount(0), vao(0)
{
	this->vbo[0] = 0;
	this->vbo[1] = 1;
}

GameModel::~GameModel()
{
}
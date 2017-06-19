#ifndef GAME_MODEL_OBJECT_H
#define GAME_MODEL_OBJECT_H

#include "sb6.h"

enum class ModelName
{
	Cube, 
	Pyramid,
	Star, 
	Lighting, 

};

class GameModel_Object
{
public:
	GameModel_Object(ModelName modelName, const char * const modelFileName);
	void ActivateModel();
	GLuint LocateModel(const char * modelName);

private:
	bool createModelObject(GLuint &modelObject, const char * const modelFileName);
	bool handleModleObject(GLuint &modelObject, const char * const modelFileName, GLenum modelType);

public:
	/* ----------------------------- DATA ------------------------------- */
	ModelName name;
	GLuint modelObject;
};
#endif // !GAME_MODEL_OBJECT_H

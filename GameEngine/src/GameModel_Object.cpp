//#include <sb6.h>
//#include <math.h>
//#include <assert.h>
//
//#include "GameObject.h"
//#include "MathEngine.h"
//#include "File.h"
//#include "GameModel_Object.h"
//#include "Game.h"
//
//GameModel_Object::GameModel_Object(ModelName modelName, const char * const modelFileName)
//	: name(modelName)
//{
//	assert(modelFileName != 0);
//	this->createModelObject(this->modelObject, modelFileName);
//}
//
//GLuint GameModel_Object::LocateModel(const char * thisUniform)
//{
//	assert(thisUniform != 0);
//	GLuint location = glGetUniformLocation(this->modelObject, thisUniform);
//	assert(location != -1);//false
//
//	return location;
//}
//
//void GameModel_Object::ActivateModel()
//{
//	glUseProgram(this->modelObject);
//}
//
//bool GameModel_Object::handleModleObject(GLuint &modelObject, const char * const modelFileName, GLenum modelType)
//{
//	FileHandle thisHandle;
//	FileError thisError;
//
//	thisError = File::open(thisHandle, modelFileName, FILE_READ);
//	assert(thisError == FILE_SUCCESS);
//
//	//thisError = File::seek(thisHandle, FILE_SEEK_END, 0);
//	//assert(thisError == FILE_SUCCESS);
//
//	int fileBytes;
//	//thisError = File::tell(thisHandle, fileBytes);
//	//assert(thisError == FILE_SUCCESS);
//
//	//thisError = File::seek(thisHandle, FILE_SEEK_BEGIN, 0);
//	//assert(thisError == FILE_SUCCESS);
//
//	char *thisData = new char[ fileBytes + 1 ];
//	assert(thisData != 0);
//
//	thisError = File::read(thisHandle, thisData, fileBytes);
//	assert(thisError == FILE_SUCCESS);
//
//	const int vertSize = fileBytes;
//
//	thisError = File::read(thisHandle, thisData, fileBytes);
//	assert(thisError == FILE_SUCCESS);
//
//	const int indexSize = fileBytes;
//
//	char *vertArray = new char[ vertSize + 1];
//	char *indexArray = new char[ indexSize + 1 ];
//
//	thisError = File::read(vertArray * sizeof
//
//
//
//
//	//null termination
//	thisData[ fileBytes ] = 0;
//
//	thisError = File::close(thisHandle);
//	assert(thisError == FILE_SUCCESS);
//
//
//	//error check:
//	GLint status = 0;
//
//	glGetShaderiv(modelObject, GL_COMPILE_STATUS, &status);
//	if(!status)
//	{
//		char buffer[4096];
//		glGetShaderInfoLog(modelObject, 4096, NULL, buffer);
//		printf("ERROR(ShaderHandler.cpp) %s: %s\n", modelFileName); //, buffer);
//		
//		glDeleteShader(modelObject);
//		assert(false);
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
//
//bool GameModel_Object::createModelObject(GLuint &modelObject, const char * const modelFileName)
//{
//	bool status;
//	char nameBuffer[ 128 ];
//
//	assert(modelFileName != 0);
//
//	strcpy_s(nameBuffer, 128, modelFileName);
//	strcat_s(nameBuffer, 128, ".model");
//
//	GLuint fs;
//	status = handleModleObject(fs, nameBuffer, GL_ELEMENT_ARRAY_BUFFER);
//	assert(status == true);
//}
#include <sb6.h>
#include <math.h>
#include <assert.h>

#include "GameObject.h"
#include "MathEngine.h"
#include "File.h"
#include "ShaderObject.h"
#include "Game.h"

ShaderObject::ShaderObject(ShaderName thisName, const char* const thisFileName)
	: name(thisName)
{
	assert(thisFileName != 0);
	this->createShaderObject(this->programObject, thisFileName);
}

GLuint ShaderObject::LocateShader(const char* thisUniform)
{
	assert(thisUniform != 0);
	GLuint location = glGetUniformLocation(this->programObject, thisUniform);
	assert(location != -1); //false

	return location;
}

void ShaderObject::ActivateShader()
{
	//shader setup
	glUseProgram(this->programObject);
}

bool ShaderObject::handleShaderObject(GLuint &thisShader, const char* const thisFileName, GLenum thisType)
{
	FileHandle thisHandle;
	FileError thisError;

	thisError = File::open(thisHandle, thisFileName, FILE_READ);
	assert(thisError == FILE_SUCCESS);

	thisError = File::seek(thisHandle, FILE_SEEK_END, 0);
	assert(thisError == FILE_SUCCESS);

	int fileBytes;
	thisError = File::tell(thisHandle, fileBytes);
	assert(thisError == FILE_SUCCESS);

	thisError = File::seek(thisHandle, FILE_SEEK_BEGIN, 0);
	assert(thisError == FILE_SUCCESS);

	char *thisData = new char[ fileBytes + 1 ];
	assert(thisData != 0);

	thisError = File::read(thisHandle, thisData, fileBytes);
	assert(thisError == FILE_SUCCESS);

	//null termination
	thisData[ fileBytes ] = 0;

	thisError = File::close(thisHandle);
	assert(thisError == FILE_SUCCESS);

	//create the shader object
	thisShader = glCreateShader(thisType);
	assert(thisShader != 0);

	//load shader
	glShaderSource(thisShader, 1, &thisData, 0);
	delete[] thisData;

	glCompileShader(thisShader);

	//error check:
	GLint status = 0;
	glGetShaderiv(thisShader, GL_COMPILE_STATUS, &status);

	if(!status)
	{
		char buffer[4096];
		glGetShaderInfoLog(thisShader, 4096, NULL, buffer);
		printf("ERROR(ShaderHandler.cpp) %s: %s\n", thisFileName); //, buffer);
		
		glDeleteShader(thisShader);
		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}
	bool ShaderObject::createShaderObject(GLuint &thisShader, const char* const thisFileName)
{

	bool status;
	char nameBuffer[ 128 ];

	assert(thisFileName != 0);

	strcpy_s(nameBuffer, 128, thisFileName);
	strcat_s(nameBuffer, 128, ".fs.glsl");

	GLuint fs;
	status = handleShaderObject(fs, nameBuffer, GL_FRAGMENT_SHADER);
	assert(status == true);

	strcpy_s(nameBuffer, 128, thisFileName);
	strcat_s(nameBuffer, 128, ".vs.glsl");

	GLuint vs;
	status = handleShaderObject(vs, nameBuffer, GL_VERTEX_SHADER);
	assert(status == true);

	//create the empty program object
	thisShader = glCreateProgram();

	//attach a shader object to a program object
	glAttachShader(thisShader, vs);
	glAttachShader(thisShader, fs);

	//lind a program object
	glLinkProgram(thisShader);

	return true;

}

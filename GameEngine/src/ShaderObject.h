#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb6.h"

enum class ShaderName
{
	Color_LIGHT,
	Texture_SIMPLE,
	Texture_POINT_LIGHT,
};

class ShaderObject
{
public:
	ShaderObject(ShaderName shaderName, const char * const shaderFileName);
	void ActivateShader();
	GLuint LocateShader(const char* shaderName);

private:
	bool createShaderObject(GLuint &programObject, const char* const shaderFileName);
	bool handleShaderObject(GLuint &shaderObject, const char* const shaderFileName, GLenum shaderType);

public:
	/* ----------------------------- DATA ------------------------------- */
	ShaderName	name;
	GLuint		programObject;
};

#endif


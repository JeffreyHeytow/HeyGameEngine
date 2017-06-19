#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include "sb6.h"

#define TEXTURE_NAME_SIZE 64

enum class TextureName
{
	ME,
	DOT_COM,
	BRICK,
	SHIP,
	NO_TEXTURE_LOADED
};

class NodeHelper
{

public:
	NodeHelper()
	{
		this->nextNode = 0;
		this->prevNode = 0;
	}

	NodeHelper *nextNode;
	NodeHelper *prevNode;

};

class TextureNode : public NodeHelper
{

public:
	TextureNode();
	void set(	const char * const thisAsset, 
				TextureName thisName, 
				GLuint thisTexture, 
				GLenum minFilter, 
				GLenum magFilter, 
				GLenum wrapper					);

	TextureName textName;
	GLuint TextID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum wrapper;


private:
	char assetName[ TEXTURE_NAME_SIZE ];

};
#endif // !TEXTURE_NODE_H

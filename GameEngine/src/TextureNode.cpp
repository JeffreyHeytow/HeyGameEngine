#include <string.h>
#include <sb6.h>

#include "TextureNode.h"

TextureNode::TextureNode()
	: textName(TextureName::NO_TEXTURE_LOADED), TextID(0), minFilter(GL_LINEAR),
	magFilter(GL_LINEAR), wrapper(GL_CLAMP_TO_EDGE)
{
	memset(this->assetName, 0, TEXTURE_NAME_SIZE);
}

void TextureNode::set(const char *const thisAsset, 
					  TextureName thisName, 
					  GLuint thisID,
					  GLenum min, 
					  GLenum mag, 
					  GLenum wrap)
{
	memcpy(this->assetName, thisAsset, TEXTURE_NAME_SIZE - 1);
	this->textName = thisName;
	this->minFilter = min;
	this->magFilter = mag;
	this->wrapper = wrap;
	this->TextID = thisID;
}
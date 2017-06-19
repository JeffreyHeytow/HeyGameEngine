#include <stdlib.h>
#include <sb6.h>
#include <assert.h>

//define tga header, local use only
#pragma pack(1)
typedef struct
{
	GLbyte size;		// size of the id field that follows header(0)
	GLbyte mapType;		// 0 = none, 1 = paletted
	GLbyte imageType;	// 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8 = rle
	
	unsigned short mapStart;	//first color map entry
	unsigned short mapLength;	//number of colors
	unsigned char  mapBits;		//bits per palette
	unsigned short xOrigin;		//image x position
	unsigned short yOrigin;		//image y position;
	unsigned short w;			//image width in pixels
	unsigned short h;			//image height in pixels

	GLbyte bits;		//bits per pixel
	GLbyte description;	//image description

}TGAFILE;
#pragma pack(8)

#include "TextureNode.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
	this->activeNode = 0;
}

TextureManager *TextureManager::instanceOf()
{
	//this is where the texture is stored in the bss
	static TextureManager thisManager;
	return &thisManager;
}

void TextureManager::addTexture(const char *const thisAsset, const TextureName thisName)
{
	GLuint tempText;
	GLuint *pTempText = &tempText;

	//Get the instance from the manager
	TextureManager *thisManager = TextureManager::instanceOf();

	//losd the texture and get the ID
	thisManager->managerLoadTexture(thisAsset, pTempText);

	//ceate a texture node
	TextureNode *thisNode = new TextureNode();

	//initialize it
	thisNode->set(thisAsset, thisName, tempText, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	//add it to the manager
	thisManager->managerAddToFront(thisNode, thisManager->activeNode);
}

GLuint TextureManager::findTexture( const TextureName thisText )
{
	TextureManager *thisManager = TextureManager::instanceOf();

	TextureNode *thisNode = (TextureNode *)thisManager->activeNode;
	while(thisNode != 0)
	{
		if(thisNode->textName == thisText)
		{
			//bingo baby
			break;
		}
		thisNode = (TextureNode *)thisNode->nextNode;
	}
	return thisNode->TextID;
}

void TextureManager::deleteTexture()
{
	TextureManager *thisManager = TextureManager::instanceOf();
	TextureNode *thisNode = (TextureNode *)thisManager->activeNode;

	while(thisNode != 0)
	{
		glDeleteTextures(1, &thisNode->TextID);

		thisNode = (TextureNode *)thisNode->nextNode;
	}
}

void TextureManager::managerAddToFront(NodeHelper *thisNode, NodeHelper *&head)
{
	assert(thisNode != 0);

	if(head == 0)
	{
		head = thisNode;
		thisNode->nextNode = 0;
		thisNode->prevNode = 0;
	}
	else
	{
		thisNode->nextNode = head;
		thisNode->prevNode = thisNode;
		head =thisNode;
	}
}

void TextureManager::managerLoadTexture(const char * const thisAsset, GLuint *&thisTexture)
{
	//get an ID for the Texture
	glGenTextures(1, thisTexture);
	//bind it
	glBindTexture(GL_TEXTURE_2D, *thisTexture);
	//Load the texture
	this->managerLoadTGAFile(thisAsset, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

bool TextureManager::managerLoadTGAFile(const char *fileName, GLenum min, GLenum mag, GLenum wrap)
{
	GLbyte *thisBit;
	int thisW, thisH, thisComp;
	GLenum thisFormat;

	//read the texture bits
	thisBit = glReadTGA(fileName, &thisW, &thisH, &thisComp, &thisFormat);
	if(thisBit == NULL)
	{
		return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, thisComp, thisW, thisH, 0, thisFormat, GL_UNSIGNED_BYTE, thisBit);

	free(thisBit);

	if(	min == GL_LINEAR_MIPMAP_LINEAR	||
		min == GL_LINEAR_MIPMAP_NEAREST ||
		min == GL_NEAREST_MIPMAP_LINEAR	||
		min == GL_NEAREST_MIPMAP_NEAREST )

		glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

/*	Allocate memory and load tga bits.  Returns a pointer to the new buffer, 
	height, and width of the texture, and the OpenGL format of data.  Call free()
	on buffer when finished.  This only works on non-palette targas without RLE coding. */
GLbyte *TextureManager::glReadTGA(	const char *thisFile, 
									GLint *thisWidth, 
									GLint *thisHeight, 
									GLint *thisComp, 
									GLenum *thisFormat		)
{
	FILE *newFile;		//file pointer
	TGAFILE tgaHeader;	//TGA file header
	unsigned long imageSize;	//size in bytes of the image
	short pixelDepth;	//pixel depth
	GLbyte *bits = NULL;	//bits pointer

	//Defailt (Failed) values
	*thisWidth = 0;
	*thisHeight = 0;
	*thisFormat = GL_RGB;
	*thisComp = GL_RGB;

	//attempt to open the file
	fopen_s(&newFile, thisFile, "rb");
	if(newFile == NULL)
	{
		return NULL;
	}

	//read in the header
	fread(&tgaHeader, 18, 1, newFile);

	//get w, h...
	*thisWidth = tgaHeader.w;
	*thisHeight = tgaHeader.h;
	pixelDepth = tgaHeader.bits / 8;

	//verify that the tga is only 8, 24, or 32 bits
	if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
	{
		return NULL;
	}

	//calculate the buffer size
	imageSize = tgaHeader.w * tgaHeader.h * pixelDepth;

	//allocate the memory and verify success
	bits = (GLbyte *)malloc(imageSize * sizeof(GLbyte));
	if(bits == NULL)
	{
		return NULL;
	}

	//read in the bits and check for a read error
	if(fread(bits, imageSize, 1, newFile) != 1)
	{
		free(bits);
		return NULL;
	}

	//set expected openGL format
	switch(pixelDepth)
	{
	case 3: //most likely case
		*thisFormat = GL_BGR;
		*thisComp = GL_RGB;
		break;

	case 4:
		*thisFormat = GL_BGRA;
		*thisComp = GL_RGBA;
		break;

	case 1:
		assert(false);
		break;

	default:
		break;
	}

	//done with file
	fclose(newFile);

	return bits;
}

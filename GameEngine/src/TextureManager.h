#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "sb6.h"
#include "TextureNode.h"

class TextureManager
{
public:
	static void addTexture(const char *const assetName, const TextureName textName);
	static void deleteTexture();
	static GLuint findTexture(const TextureName thisText);

private:
	static TextureManager *instanceOf();
	TextureManager();

	void managerLoadTexture(const char *const thisAsset, GLuint *&thisID);
	bool managerLoadTGAFile(const char *thisTGA, GLenum min, GLenum mag, GLenum wrap);
	void managerAddToFront(NodeHelper *thisNode, NodeHelper *&headNode);
	GLbyte *glReadTGA(	const char *thisFIle, 
						GLint *thisWidth, 
						GLint *thisHeight, 
						GLint *numComponents, 
						GLenum *thisFormat		);

	/* ----------------------------- DATA ------------------------------- */

	NodeHelper *activeNode;
};

#endif // !TEXTURE_MANAGER_H

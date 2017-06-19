#include <assert.h>
#include "MathEngine.h"
#include "GraphicTexture.h"
#include "ProcessGraphic_Texture.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Camera_Manager.h"

//extern Camera *worldCamera;

ProcessGraphic_Texture::ProcessGraphic_Texture(ShaderObject *thisShader)
	: ProcessGraphic(thisShader), type(ProcessGraphic::GraphicType::FlatTexture)
{

}

void ProcessGraphic_Texture::GameState(GraphicObject *thisGraphic)
{
	GraphicTexture *thisTexture = (GraphicTexture *)thisGraphic;
	glActiveTexture(GL_TEXTURE0);
	//bind teh texture
	GLuint thisID = TextureManager::findTexture(thisTexture->textureName);
	glBindTexture(GL_TEXTURE_2D, thisID);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void ProcessGraphic_Texture::DrawGame(GraphicObject *drawObject)
{
	//back poiner
	GraphicTexture *thisObject = (GraphicTexture *)drawObject;
	Camera *thisCamera = Camera_Manager::getActiveCamera();

	//draw
	//set the vao
	glBindVertexArray(thisObject->getModel()->vao);

	//use the shader
	this->renderShader->ActivateShader();

	Matrix worldMatrix = thisObject->getWorldMatrix();
	Matrix viewMatrix = thisCamera->getViewMatrix();
	Matrix projMatrix =  thisCamera->getProjMatrix();

	glUniformMatrix4fv(this->renderShader->LocateShader("proj_matrix"), 1, GL_FALSE, (float *)&projMatrix);
	glUniformMatrix4fv(this->renderShader->LocateShader("view_matrix"), 1, GL_FALSE, (float *)&viewMatrix);
	glUniformMatrix4fv(this->renderShader->LocateShader("world_matrix"), 1, GL_FALSE, (float *)&worldMatrix);

	//draw it
	//glDrawArrays(GL_TRIANGLES, 0, (3 * thisObject->getModel()->vertCount));
	glDrawElements(GL_TRIANGLES, 3 * thisObject->getModel()->trisCount, GL_UNSIGNED_INT, 0);
}
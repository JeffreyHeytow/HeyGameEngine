#include <assert.h>
#include "MathEngine.h"
#include "GraphicLighting.h"
#include "ProcessGraphic_Lighting.h"
#include "TextureManager.h"
#include "Camera_Manager.h"

//extern Camera *worldCamera;

ProcessGraphic_Lighting::ProcessGraphic_Lighting(ShaderObject *thisShader)
	: ProcessGraphic(thisShader), lightType(ProcessGraphic::GraphicType::TextureLighting)
{

}

void ProcessGraphic_Lighting::GameState(GraphicObject *thisGraphic)
{
	GraphicLighting *thisLight = (GraphicLighting *)thisGraphic;

	glActiveTexture(GL_TEXTURE0);

	//bind the texture
	GLuint thisTexture = TextureManager::findTexture(thisLight->lightName);
	glBindTexture(GL_TEXTURE_2D, thisTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void ProcessGraphic_Lighting::DrawGame(GraphicObject *thisGraphic)
{
	//Back Pointer
	GraphicLighting *thisObject = (GraphicLighting *)thisGraphic;
	Camera *thisCamera = Camera_Manager::getActiveCamera();

	//draw it:
	//vao setup
	glBindVertexArray(thisObject->getModel()->vao);

	//shader to use:
	this->renderShader->ActivateShader();

	Matrix thisWorld = thisObject->getWorldMatrix();
	Matrix thisFOV = thisCamera->getViewMatrix();
	Matrix thisProj = thisCamera->getProjMatrix();

	glUniformMatrix4fv(this->renderShader->LocateShader("proj_matrix"), 1, GL_FALSE, (float *)&thisProj);
	glUniformMatrix4fv(this->renderShader->LocateShader("view_matrix"), 1, GL_FALSE, (float *)&thisFOV);
	glUniformMatrix4fv(this->renderShader->LocateShader("world_matrix"), 1, GL_FALSE, (float *)&thisWorld);

	Vect lightPosition = thisObject->lightPosition;
	Vect lightColor = thisObject->lightColor;
	glUniform3fv(this->renderShader->LocateShader("vLightPos"), 1, (float *)&lightPosition);
	glUniform4fv(this->renderShader->LocateShader("vColor"), 1, (float *)&lightColor);

	//draw it
	//glDrawArrays(GL_TRIANGLES, 0, (3 * thisObject->getModel()->vertCount));

	glDrawElements(GL_TRIANGLES, 3 * thisObject->getModel()->trisCount, GL_UNSIGNED_INT, 0);
}
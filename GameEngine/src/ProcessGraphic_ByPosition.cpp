#include <assert.h>
#include "MathEngine.h"
#include "GraphicColorByPosition.h"
#include "ProcessGraphic_ByPosition.h"
#include "Camera_Manager.h"

//extern Camera *worldCamera;

ProcessGraphic_ByPosition::ProcessGraphic_ByPosition(ShaderObject *thisShader)
	: ProcessGraphic(thisShader), type(ProcessGraphic::GraphicType::ColorByPosition)
{

}

void ProcessGraphic_ByPosition::GameState(GraphicObject *thisGraphic)
{
	ProcessGraphic_ByPosition *thisObject = (ProcessGraphic_ByPosition *)thisGraphic;

	thisObject;

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void ProcessGraphic_ByPosition::DrawGame(GraphicObject *thisObject)
{
	//back pointer
	GraphicColorByPosition *bPtr = (GraphicColorByPosition *)thisObject;
	Camera *thisCamera = Camera_Manager::getActiveCamera();
	//draw it
	//set the vao
	glBindVertexArray(bPtr->getModel()->vao);
	this->renderShader->ActivateShader();

	Matrix worldMatrix = bPtr->getWorldMatrix();
	Matrix viewMatrix = thisCamera->getViewMatrix();
	Matrix projMatrix = thisCamera->getProjMatrix();

	glUniformMatrix4fv(this->renderShader->LocateShader("proj_matrix"), 1, GL_FALSE, (float *)&projMatrix);
	glUniformMatrix4fv(this->renderShader->LocateShader("view_matrix"), 1, GL_FALSE, (float *)&viewMatrix);
	glUniformMatrix4fv(this->renderShader->LocateShader("world_matrix"), 1, GL_FALSE, (float *)&worldMatrix);


	//draw
	//glDrawArrays(GL_TRIANGLES, 0, (3 * bPtr->getModel()->vertCount));

	//starting point of IBO
	glDrawElements(GL_TRIANGLES, 3 * bPtr->getModel()->trisCount, GL_UNSIGNED_INT, 0);
}
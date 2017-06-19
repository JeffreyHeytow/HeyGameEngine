#include <assert.h>
#include "MathEngine.h"
#include "GraphicWireframe.h"
#include "ProcessGraphic_Wireframe.h"
#include "Camera_Manager.h"


//extern Camera *worldCamera;

ProcessGraphic_Wireframe::ProcessGraphic_Wireframe(ShaderObject *thisShader)
	: ProcessGraphic(thisShader), type(ProcessGraphic::GraphicType::WireFrame)
{

}

void ProcessGraphic_Wireframe::GameState(GraphicObject *stateObject)
{
	ProcessGraphic_Wireframe *thisObject = (ProcessGraphic_Wireframe *)stateObject;
	thisObject;

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void ProcessGraphic_Wireframe::DrawGame(GraphicObject *drawObject)
{
	//back pointer
	GraphicWireframe *thisObject = (GraphicWireframe *)drawObject;
	Camera *thisCamera = Camera_Manager::getActiveCamera();

	//draw:
	//set the vao
	glBindVertexArray(thisObject->getModel()->vao);

	//set the state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	//use this shader
	this->renderShader->ActivateShader();

	Matrix worldMatrix = thisObject->getWorldMatrix();
	Matrix viewMatrix = thisCamera->getViewMatrix();
	Matrix projMatrix =  thisCamera->getProjMatrix();

	glUniformMatrix4fv(this->renderShader->LocateShader("proj_matrix"), 1, GL_FALSE, (float *)&projMatrix);
	glUniformMatrix4fv(this->renderShader->LocateShader("view_matrix"), 1, GL_FALSE, (float *)&viewMatrix);
	glUniformMatrix4fv(this->renderShader->LocateShader("world_matrix"), 1, GL_FALSE, (float *)&worldMatrix);

	//actual draw
	//glDrawArrays(GL_TRIANGLES, 0, (3 * thisObject->getModel()->vertCount));
	glDrawElements(GL_TRIANGLES, 3 * thisObject->getModel()->trisCount, GL_UNSIGNED_INT, 0);

	//restore state
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
#include "GameLibrary.h"

/* NO GLOBALS! BAD! */
//Camera *worldCamera = 0;
//make a singleton?

/*  
	Game::Game() : 
		Game HeyEngine Constructor 
*/
Game::Game( const char* thisWinName, const int thisWinWidth, const int thisWinHeight )
	: HeyEngine( thisWinName, thisWinWidth, thisWinHeight )
{

}

/*	Game::InitializeGame() :
		Allows the HeyEngine to inititialize anything it needs to 
		before the game is run. This is where a query for any required
		services can be made, and any non-graphic related content can
		be loaded 
*/
void Game::InitializeGame()
{
	InputManager::CreateInput();

}

/*	Game::LoadGameContent() :
		Allows the loading of all content needed for the HeyEngine
		such as object, grpahic, data, ect...
*/
void Game::LoadGameContent()
{
	Camera *thisCamera = Camera_Manager::getActiveCamera();


	//camera setup:
	thisCamera = new Camera(CameraName::Camera_01);
	thisCamera->setCameraViewport(0, 0, (int)this->screenWidth, (int)this->screenHeight);
	thisCamera->setCameraPerspective(50.0f, (this->screenWidth / this->screenHeight), 0.5f, 1000.0f);
	thisCamera->setCameraOrientation(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 1.0f, 4.0f));
	thisCamera->updateCamera();
	Camera_Manager::setCamera1(thisCamera);
	Camera_Manager::setActiveCamera(thisCamera);
	Camera_Manager::addCamera(thisCamera);

	thisCamera = new Camera(CameraName::Camera_02);
	thisCamera->setCameraViewport(0, 0, (int)this->screenWidth, (int)this->screenHeight);
	thisCamera->setCameraPerspective(50.0f, (this->screenWidth / this->screenHeight), 0.5f, 4000.0f);
	thisCamera->setCameraOrientation(Vect(0.25f, 1.0f, 0.0f), Vect(1.0f, 0.0f, 0.0f), Vect(1.0f, 3.0f, 6.0f));
	thisCamera->updateCamera();
	Camera_Manager::setCamera2(thisCamera);
	Camera_Manager::addCamera(thisCamera);

	thisCamera = new Camera(CameraName::Camera_03);
	thisCamera->setCameraViewport(0, 0, (int)this->screenWidth, (int)this->screenHeight);
	thisCamera->setCameraPerspective(50.0f, (this->screenWidth / this->screenHeight), 1.0f, 1000.0f);
	thisCamera->setCameraOrientation(Vect(2.0f, 5.0f, -2.0f), Vect(0.023f, 0.23f, 0.23f), Vect(-1.0f, -2.0f, -10.0f));
	thisCamera->updateCamera();
	Camera_Manager::setCamera3(thisCamera);
	Camera_Manager::addCamera(thisCamera);


	//load the model:
	GameModel_Cube *thisCube = new GameModel_Cube("cubeModel.bin");
	GameModel_Pyramid *thisPyramid = new GameModel_Pyramid("pyramidModel.bin");
	GameModel_Star *thisStar = new GameModel_Star("HeytowStar.model");
	GameModel_Octo *thisOcto = new GameModel_Octo("octoHedronModel.bin");

	//create and load the shader
	ShaderObject *thisShader_color = new ShaderObject(ShaderName::Color_LIGHT, "colorRender");
	ShaderObject *thisShader_texture = new ShaderObject(ShaderName::Texture_SIMPLE, "textureRender");
	ShaderObject *thisShder_lighting = new ShaderObject(ShaderName::Texture_POINT_LIGHT, "LightDiffRender");

	//TEXTURE
	TextureManager::addTexture("RedBrick.tga", TextureName::BRICK);
	TextureManager::addTexture("JH.tga", TextureName::ME);
	TextureManager::addTexture("jhdotcom.tga", TextureName::DOT_COM);
	TextureManager::addTexture("ship.tga", TextureName::SHIP);

	//setuup renderer
	ProcessGraphic_ByPosition *thisByPosition = new ProcessGraphic_ByPosition(thisShader_color);
	ProcessGraphic_Wireframe *thisWire = new ProcessGraphic_Wireframe(thisShader_color);
	ProcessGraphic_Texture *thisText = new ProcessGraphic_Texture(thisShader_texture);
	ProcessGraphic_Lighting *thisLight = new ProcessGraphic_Lighting(thisShder_lighting);

	//Graphic object for a specific instance
	GraphicColorByPosition *thisGraphicByPosition;
	GraphicWireframe *thisWireframe;
	GraphicTexture *thisTexture;
	GraphicLighting *thisLighting;

	//create gameObjects
	GameObject *thisObject;

	/*------------------------------------------ MAN ----------------------------------------------*/
	thisGraphicByPosition = new GraphicColorByPosition(thisPyramid, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.1f, -0.75f, -1.5f));
	thisObject->rotDelta = 0.0007f;
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisPyramid, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-0.33f, -0.75f, -1.5f));
	thisObject->rotDelta = 0.0007f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::DOT_COM);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.12f, 0.25f, -1.5f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::DOT_COM);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.12f, 0.75f, -1.5f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisOcto, thisText, TextureName::ME);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.12f, 1.5f, -1.5f));
	thisObject->rotZ = 0.00035f;
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisPyramid, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-0.33f, 0.9f, -1.01f));
	thisObject->rotZ = -0.0003f;
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisPyramid, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.22f, 0.25f, -1.12f));
	GameObject_Manager::addObject(thisObject);



	/*------------------------------------------ WALL 1 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, 0.0f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, 0.0f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 2 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, -0.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, -0.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 1.0f, -0.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 2 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, -0.8f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, -0.8f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.0f, -0.8f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 1.5f, -0.8f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 3 ----------------------------------------------*/
    thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.0f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.5f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 2.0f, -1.2f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 4 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.0f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.5f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 2.0f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 2.5, -1.6f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 5 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.0f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.5f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 2.0f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 2.5f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 3.0f, -2.0));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 6 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 0.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 1.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 2.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 2.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-2.0f, 3.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-2.0f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);


	/*------------------------------------------ WALL 7 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.5f, 0.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.5f, 0.5, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.5f, 1.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.5f, 1.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.5f, 2.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.5f, 2.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.5f, 3.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-1.5f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.0f, 0.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.0f, 0.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.0f, 1.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.0f, 1.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.0f, 2.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-1.0f, 2.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-1.0f, 3.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-1.0f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.5f, 0.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-0.5, 0.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.5f, 1.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-0.5, 1.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.5f, 2.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(-0.5, 2.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(-0.5f, 3.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(-0.5f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.0f, 0.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.0f, 0.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.0f, 1.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.0f, 1.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.0f, 2.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.0f, 2.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.0f, 3.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(0.0f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.5f, 0.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.5f, 0.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.5f, 1.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.5f, 1.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.5f, 2.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(0.5f, 2.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(0.5f, 3.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(0.5f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.0f, 0.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.0f, 0.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.0f, 1.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.0f, 1.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.0f, 2.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.0f, 2.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.0f, 3.0f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(1.0f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.5f, 0.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.5f, 0.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.5f, 1.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.5f, 1.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.5f, 2.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisGraphicByPosition = new GraphicColorByPosition(thisOcto, thisByPosition);
	thisObject = new GameObject(thisGraphicByPosition);
	thisObject->setObjectPosition(Vect(1.5f, 2.5f, -2.4f));
	thisObject->setObjectScale(Vect(0.25f, 0.25f, 0.25f));
	thisObject->rotDelta = 0.007f;
	thisObject->rotZ = 0.005f;
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(1.5f, 3.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(1.5f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);


/*------------------------------------------ WALL 8 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 2.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 2.5f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 3.0f, -2.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 3.5f, -2.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);


/*------------------------------------------ WALL 9 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, 0.0f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, 0.0f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 10 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, -0.4f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, -0.4f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 1.0f, -0.4f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 11 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, -0.8f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, -0.8f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.0f, -0.8f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 1.5f, -0.8f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 12 ----------------------------------------------*/
    thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.0f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.5f, -1.2f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 2.0f, -1.2f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 13 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.0f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.5f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 2.0f, -1.6f));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 2.5, -1.6f));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);

	/*------------------------------------------ WALL 14 ----------------------------------------------*/
	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.0f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 0.5f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.0f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 1.5f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 2.0f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisTexture = new GraphicTexture(thisCube, thisText, TextureName::BRICK);
	thisObject = new GameObject(thisTexture);
	thisObject->setObjectPosition(Vect(2.0f, 2.5f, -2.0));
	GameObject_Manager::addObject(thisObject);

	thisWireframe = new GraphicWireframe(thisPyramid, thisWire);
	thisObject = new GameObject(thisWireframe);
	thisObject->setObjectPosition(Vect(2.0f, 3.0f, -2.0));
	thisObject->rotDelta = 0.00004f;
	GameObject_Manager::addObject(thisObject);


	/*------------------------------------------ SPACESHIPS ----------------------------------------------*/
	Vect color1(1.0f, 1.0f, 1.0f, 0.0f);
	Vect pos1( 1, 1, 1);
	thisLighting = new GraphicLighting( thisStar, thisLight, TextureName::SHIP, color1, pos1);
	thisObject = new GameObject( thisLighting );
	thisObject->setObjectPosition( Vect(-0.8f, 5.0f, 2.5f));
	thisObject->setObjectScale(Vect(4.0f, 2.0f, 6.0f));
	thisObject->rotDelta = 0.00055f;
	thisObject->rotZ = 0.0002f;
	GameObject_Manager::addObject( thisObject );

	Vect color2(1.0f, 0.44f, 0.12f, 0.0f);
	Vect pos2( 1, 0, 1);
	thisLighting = new GraphicLighting( thisStar, thisLight, TextureName::SHIP, color2, pos2);
	thisObject = new GameObject( thisLighting );
	thisObject->setObjectPosition( Vect(1.6f, 6.5f, -1.4f));
	thisObject->setObjectScale(Vect(4.0f, 2.0f, 6.0f));
	thisObject->rotDelta = 0.00055f;
	thisObject->rotZ = 0.0002f;
	GameObject_Manager::addObject( thisObject );

	Vect color3(1.0f, 1.0f, 1.0f, 0.0f);
	Vect pos3( 0, 1, 1);
	thisLighting = new GraphicLighting( thisStar, thisLight, TextureName::SHIP, color3, pos3);
	thisObject = new GameObject( thisLighting );
	thisObject->setObjectPosition( Vect(-1.1f, 9.0f, -3.3f));
	thisObject->setObjectScale(Vect(4.0f, 2.0f, 6.0f));
	thisObject->rotDelta = 0.00055f;
	thisObject->rotZ = 0.0002f;
	GameObject_Manager::addObject( thisObject );

	Vect color4(0.61f, 0.44f, 0.12f, 0.0f);
	Vect pos4( 1, 1, 0);
	thisLighting = new GraphicLighting( thisStar, thisLight, TextureName::SHIP, color4, pos4);
	thisObject = new GameObject( thisLighting );
	thisObject->setObjectPosition( Vect(2.7f, 4.0f, 4.1f));
	thisObject->setObjectScale(Vect(4.0f, 2.0f, 6.0f));
	thisObject->rotDelta = 0.00055f;
	thisObject->rotZ = 0.0002f;
	GameObject_Manager::addObject( thisObject );


}

/*	Game::UpdateGame() :
		Called once per frame to update data, transformations, etc..
		This function is used to control the process order of
		Input, AI, Physics, Animation and Graphics. 
*/
void Game::UpdateGame( float currentTime )
{
	currentTime;
	/*worldCamera->updateCamera();*/

	Camera_Manager::updateGameCamera();
	GameObject_Manager::updateObject(currentTime);
}

/*	Game::DrawGame() :
		Called once per frame to draw graphics to the screen.
		This function is ONLY used for RENDERING.
*/
void Game::DrawGame()
{
	//worldObject->getGraphic()->RenderGraphic();
	//worldObject2->getGraphic()->RenderGraphic();
	/*worldObject3->getGraphic()->RenderGraphic();*/

	GameObject_Manager::drawObject();
}

/*	Game::UnloadGameContent() :
		Unloads all game content that was loaded into
		the HeyEngine before the game loop started.
*/
void Game::UnLoadGameContent()
{
	//glDeleteVertexArrays(1, &vao);
	//glDeleteProgram(worldShader->programObject);
	//glDeleteBuffers(1, &buffer);
}

/*	Game::ScreenResize() :
		Scales the width and the height of the screen size
*/
//void Game::onResize( int w, int h)
//{
//	HeyEngine::onResize(w, h);
//
//	//aspect = (float)w / (float)h;
//
//	//vmath::mat4 proj_matrix = (vmath::perspective(50.0f, aspect, 0.1f, 1000.0f));
//	//projMatrix = (Matrix &)proj_matrix;
//
//	//projectionMatrix = &projMatrix;
//}

/*	Game::CleanBufferFunc() :
		Permits changes to the way the clear buffer function works
*/
void Game::ClearBufferFunc()
{
	const GLfloat blue[] = { 0.0f, 0.1f, 0.3f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, blue);
	glClearBufferfv(GL_DEPTH, 0, &one);
}
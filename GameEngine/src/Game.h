#ifndef GAME_H
#define GAME_H

#include "HeyEngine.h"
#include "MathEngine.h"
#include <sb6.h>
#include <math.h>
#include <vmath.h>

class Game : public HeyEngine
{

public:
	Game( const char* winName, const int winWidth, const int winHeight );

	virtual void InitializeGame();
	virtual void LoadGameContent();
	virtual void UpdateGame(float currentTime);
	virtual void DrawGame();
	virtual void UnLoadGameContent();

	virtual void ClearBufferFunc();

	//virtual void onResize( int w, int h );

	float screenWidth;
	float screenHeight;
	float  aspect;

private:
	//prevent from calling the wrong call
	Game();


	/* ----------------------------- DATA ------------------------------- */

	//GLuint program;
	//GLuint vao;
	//GLuint buffer;
	//GLint  mv_location;
	//GLint  proj_location;


};

#endif
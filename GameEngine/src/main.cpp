#include <assert.h>
#include "sb6.h"
#include "Game.h"
#include "File.h"
#include "PCSTree.h"
#include "PCSNode.h"

int CALLBACK WinMain(HINSTANCE,  HINSTANCE,  LPSTR, int)                  
{        
    Game *heyGame = new Game("HeyGame", 800, 600);    
	heyGame->screenHeight = 800.0f;
	heyGame->screenWidth = 600.0f;
    heyGame->run();                                  
    return 0;                                       
}
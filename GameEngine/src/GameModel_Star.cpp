#include <sb6.h>
#include <assert.h>
#include "GameModel_Star.h"

struct VertCoordinate_Star
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float lx;
	float ly;
	float lz;
};

struct tri_index_star
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

};

#define TRILIST_TRIANGLE_COUNT (sizeof(tri_List) / sizeof(tri_index_star))

tri_index_star tri_List[] =
{
	{ 0, 1, 6 },
	{ 0, 6, 1 },
	{ 5 , 1, 6},
	{ 5, 6, 1 },

	{ 0, 2, 6 },
	{ 0, 6, 2 },
	{ 5, 6, 2 },
	{ 5, 2, 6 },

	{ 0, 3, 6 },
	{0, 6, 3 },
	{5, 3, 6 },
	{5, 6, 3},

	{ 0, 4, 6 },
	{ 0, 6, 4 },
	{ 5, 4, 6 },
	{ 5, 6, 4 },

	{0, 1, 3 },
	{ 0, 1, 2 },
	{ 0, 2, 1 },
	{0, 2, 3},
	{0, 3, 2},
	{0, 3, 4},
	{0, 4, 3},
	{0, 4, 1},
	{0, 1, 4}

};

#define CUBE_DATA_VERT_COUNT (sizeof(cubePositions)/sizeof(VertCoordinate_Star))

VertCoordinate_Star cubePositions[] =
{
	{ 0.0f, 0.50f, 0.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.0f },	//0
	{ -0.50f, 0.25f, 0.0f, 0.0f, 0.0f, -0.6f, 0.6f, 0.6f },	//1
	{ 0.0f, 0.25f, -0.25f, 1.0f, 1.0f, 0.6f, 0.6f, -0.6f },		//2

	{ 0.50f, 0.25f, 0.0f, 0.0f, 0.0f, 0.6f, 0.6f, 0.6f },	//3
	{ 0.0f, 0.25f, 0.25, 1.0f, 1.0f, 0.6f, 0.0f, 0.0f },		//4
	{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f },		//5
	{ 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.6f, 0.6f, 0.6f }		//6
};

GameModel_Star::GameModel_Star(const char* const thisFileName)
	: GameModel()
{
	this->generateVAO(thisFileName);
}

GameModel_Star::~GameModel_Star()
{
	//remove anything dynamic here!
}

void GameModel_Star::generateVAO(const char* const vaoFileName)
{
	//future use
	vaoFileName;

	this->vertCount = CUBE_DATA_VERT_COUNT;
	this->trisCount = TRILIST_TRIANGLE_COUNT;

	//create the vao;
	glGenVertexArrays(1, &this->vao);
	assert(this-vao != 0);
	glBindVertexArray(this->vao);

	//create the vbo
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);

	/*---------------- load combined data ----------------*/

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

	//load data to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertCoordinate_Star) * this->vertCount, cubePositions, GL_STATIC_DRAW);

	//vertex data in location 0:
	void *vertOffset = (void *)((unsigned int)&cubePositions[0].x - (unsigned int)cubePositions);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertCoordinate_Star), vertOffset);
	glEnableVertexAttribArray(0);

	//texture data in location 1:
	void *textOffset = (void*)((unsigned int)&cubePositions[0].u - (unsigned int)cubePositions);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertCoordinate_Star), textOffset);
	glEnableVertexAttribArray(1);

	//norm data in location 2:
	void *normOffset = (void *)((unsigned int)&cubePositions[0].lx - (unsigned int)cubePositions);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertCoordinate_Star), normOffset);
	glEnableVertexAttribArray(2);

	/*---------------- load index data ----------------*/

	//bind the 2nd vbo as being the active buffer and storing index:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	//copy the index data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_index_star) * this->trisCount, tri_List, GL_STATIC_DRAW);
}
#include <sb6.h>
#include <assert.h>
#include "GameModel_Cube.h"
#include "File.h"


struct VertCoordinate
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

struct tri_index
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

};

GameModel_Cube::GameModel_Cube(const char* const thisFileName)
	: GameModel()
{
	this->generateVAO(thisFileName);
}

GameModel_Cube::~GameModel_Cube()
{
	//remove anything dynamic here!
}

void GameModel_Cube::generateVAO(const char* const vaoFileName)
{
	FileHandle file;
	FileError error;

	int sizeOfTriIndex = 0;
	int numberOfTriIndices = 0;

	/*
	Open the model file that has been passed in
	*/
	error = File::open(file, vaoFileName, FILE_READ);
	assert(error == FILE_SUCCESS);

	/*
	Seek to the end of the file, this will be used for size
	*/
	error = File::seek(file, FILE_SEEK_END, 0);
	assert(error == FILE_SUCCESS);

	/*
	Store the size of the file in bytes
	*/
	int sizeOfFile = 0;
	error = File::tell(file, sizeOfFile);
	assert(error == FILE_SUCCESS);

	/*
	Seek back to the beginning of file to begin transfer from disk to ram
	*/
	error = File::seek(file, FILE_SEEK_BEGIN, 0);
	assert (error == FILE_SUCCESS);

	/*
	Create buffer to map file into ram
	*/
	char* dataBuffer = new char[sizeOfFile + 1];
	assert(dataBuffer != 0);

	/*
	Read the entire size from file into data buffer
	*/
	error = File::read(file, dataBuffer, sizeOfFile);
	File::close(file);

	/*
	Extract model data from .bin file
	*/
	int* intPtr = (int*)dataBuffer;
	sizeOfTriIndex = intPtr[0];
	numberOfTriIndices = intPtr[1];

	int sizeOfVerts = 0;
	int numberOfVerts = 0;

	sizeOfVerts = *(dataBuffer + (sizeof(int) * 2) + (sizeOfTriIndex * numberOfTriIndices));
	numberOfVerts = *(dataBuffer + (sizeof(int) * 2) + (sizeOfTriIndex * numberOfTriIndices) + sizeof(int));


	tri_index* indexPtr = (tri_index*)(intPtr + 2);
	VertCoordinate* ptr = (VertCoordinate*)(dataBuffer + (sizeof(int) * 2) + (sizeOfTriIndex * numberOfTriIndices) + (sizeof(int) * 2));

	this->vertCount	= numberOfVerts;
	this->trisCount	= numberOfTriIndices;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertCoordinate) * this->vertCount, ptr, GL_STATIC_DRAW);

	//vertex data in location 0:
	void *vertOffset = (void *)((unsigned int)&ptr[0].x - (unsigned int)ptr);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertCoordinate), vertOffset);
	glEnableVertexAttribArray(0);

	//texture data in location 1:
	void *textOffset = (void*)((unsigned int)&ptr[0].u - (unsigned int)ptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertCoordinate), textOffset);
	glEnableVertexAttribArray(1);

	//norm data in location 2:
	void *normOffset = (void *)((unsigned int)&ptr[0].lx - (unsigned int)ptr);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertCoordinate), normOffset);
	glEnableVertexAttribArray(2);

	/*---------------- load index data ----------------*/

	//bind the 2nd vbo as being the active buffer and storing index:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	//copy the index data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_index) * this->trisCount, indexPtr, GL_STATIC_DRAW);
}
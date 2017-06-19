#include "model2bin.h"

void model2bin::runTool()
{
	struct Vert_XYZ_UV
	{
		float x;
		float y;
		float z;

		float u;
		float v;

		float nx;
		float ny;
		float nz;
	};

	struct Tri_Index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	#define TRILIST_NUM_TRIANGLES (sizeof(Tri_List)/sizeof(Tri_Index))

	Tri_Index Tri_List[] =
	{
		{1,4,0},	
		{2,4,1},	
		{3,4,2},	
		{0,4,3},	
		{0,5,1},	
		{1,5,2},	
		{2,5,3},	
		{3,5,0},
	};

	#define CUBE_DATA_NUM_VERTS (sizeof(cubeData)/sizeof(Vert_XYZ_UV))

	static Vert_XYZ_UV cubeData[] = {

		{ .5f, 0.0f, 0.0f,		0.0f, 0.0f,		0.58f, 0.0f, 0.0f},
		{ 0.0f, -.5f, 0.0f,		1.0f, 0.0f,		0.0f, -0.58f, 0.0f},
		{ -.5f, 0.0f, 0.0f,		0.0f, 1.0f,		-0.58f, 0.0f, 0.0f},
		{ 0.0f, .5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.58f, 0.0f},
		{ 0.0f, 0.0f, .5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.58f},
		{ 0.0f, 0.0f, -.5f,		1.0f, 1.0f,		0.0f, 0.0f, -0.58f},
	};

	Tri_List;

	int header[] = {sizeof(Tri_Index), sizeof(Tri_List)/sizeof(Tri_Index)};
	int header2[] = {sizeof(Vert_XYZ_UV), sizeof(cubeData)/sizeof(Vert_XYZ_UV)};

	FileHandle file;
	FileError error;

	error = File::open(file, FILENAME, FILE_WRITE);

	error = File::write(file, &header, sizeof(header));

	error = File::write(file, &Tri_List, sizeof(Tri_List));

	error = File::write(file, &header2, sizeof(header2));

	error = File::write(file, &cubeData, sizeof(cubeData));

	error = File::close(file);

	File::open(file, FILENAME, FILE_READ);
	
	int sizeOfTriIndex = 0;
	int numberOfTriIndices = 0;

	File::read(file, &sizeOfTriIndex, sizeof(int));
	File::read(file, &numberOfTriIndices, sizeof(int));

	int* tris = (int*)malloc(sizeOfTriIndex * numberOfTriIndices);

	File::read(file, tris, sizeOfTriIndex * numberOfTriIndices);

	int sizeOfVerts = 0;
	int numberOfVerts = 0;

	File::read(file, &sizeOfVerts, sizeof(int));
	File::read(file, &numberOfVerts, sizeof(int));

	int* verts = (int*)malloc(sizeOfVerts * numberOfVerts);

	File::read(file, verts, sizeOfVerts * numberOfVerts);

	File::close(file);

	Vert_XYZ_UV* vert = (Vert_XYZ_UV*)verts;
	vert += numberOfVerts - 1;
	vert;
}
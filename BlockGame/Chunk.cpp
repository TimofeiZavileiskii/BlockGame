#include "pch.h"
#include "Chunk.h"
#include "Model.h"
#include "CubeMeshCreator.h"
#include "PerlinNoise.h"
#include "ChunkLoader.h"
#include <iostream>

BlockType* Chunk::blockTypes;

void Chunk::GenerateTerrain()
{
	blocks = new Block[chunkSize];
	PerlinNoise noise = PerlinNoise();

	for (int i = 0; i < CHUNK_DIMENSION; i++) {
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++) {
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++) {
				/*
				float height = ((float)(ii + CHUNK_DIMENSION * coordinates.y) + 0.01) / (float)40;
				float x = ((float)(i + CHUNK_DIMENSION * coordinates.x) + 0.01) / (float)40;
				float y = ((float)(iii + CHUNK_DIMENSION * coordinates.z) + 0.01) / (float)40;
				*/
				if (ii + CHUNK_DIMENSION * coordinates.y < floor(10.0f* (sin((float)(i+coordinates.x * CHUNK_DIMENSION) / 30.0f)
					+ sin((float)(iii + coordinates.z * CHUNK_DIMENSION) / 50.0f))))
				{
					blocks[GetArrayPos(i, ii, iii)] = Block(&blockTypes[STONE]);
				}
				else
				{
					blocks[GetArrayPos(i, ii, iii)] = Block(&blockTypes[AIR]);
				}
			}
		}
	}
}

void Chunk::AssignBlockTypes()
{
	blockTypes = new BlockType[BLOCK_ID_LENGTH];

	blockTypes[AIR] = BlockType(true, "");
	blockTypes[STONE] = BlockType(false, "Stone");
	blockTypes[SAND] = BlockType(false, "Sand");
	blockTypes[DIRT] = BlockType(false, "Dirt");
	blockTypes[BRICK] = BlockType(false, "Bricks");
	blockTypes[GRASS] = BlockType(false, "Grass");
}

void Chunk::GenerateChunkMesh()
{
	CubeMeshCreator cubeMesh = CubeMeshCreator(atlas);
	if (coordinates.x == 3 && coordinates.y == 0 && coordinates.z == 2)
	{
		std::cout << "Here";
	}
	for (int i = 0; i < CHUNK_DIMENSION; i++)
	{
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++)
		{
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++)
			{
				if (coordinates.x == -3 && coordinates.y == 0 && coordinates.z == 2 && i == 1 && ii == 8 && iii == 31)
				{

					std::cout << "(" << coordinates.x * CHUNK_DIMENSION + i << 
						", " << coordinates.y * CHUNK_DIMENSION + ii << ", " << coordinates.z * CHUNK_DIMENSION + iii <<")";
					std::cout << "Here";
				}

				if (!blocks[GetArrayPos(i, ii, iii)].GetTransperency())
				{
				
					int arrayPos = GetArrayPos(i, ii, iii);
					
					if (ii - 1 < 0 )
					{	
						cubeMesh.AddBottomFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii - 1, iii)].GetTransperency())
					{
						cubeMesh.AddBottomFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (ii + 1 > CHUNK_DIMENSION - 1)
					{
						cubeMesh.AddTopFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii + 1, iii)].GetTransperency()) 
					{
						cubeMesh.AddTopFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (i - 1 < 0)
					{
						cubeMesh.AddLeftFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i - 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddLeftFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (i + 1 > CHUNK_DIMENSION - 1)
					{
						cubeMesh.AddRightFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i + 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddRightFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (iii - 1 < 0)
					{
						cubeMesh.AddFrontFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii, iii - 1)].GetTransperency())
					{
						cubeMesh.AddFrontFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (iii + 1 > CHUNK_DIMENSION - 1)
					{
						cubeMesh.AddBackFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii, iii + 1)].GetTransperency())
					{
						cubeMesh.AddBackFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					
				}
			}
		}
	}
	
	/*
	if (coordinates.x == -3 && coordinates.y == 0 && coordinates.z == 2)
	{
		int count = 0;
		
		std::cout << count << ": ";

		int i = 0;
		for (float f : cubeMesh.indicies) {
			std::cout << f << ", ";
			i++;
			if (i == 3) {
				count++;
				std::cout << "\n" << count << ": ";
				i = 0;
			}
		}

		std::cout << "Here";
	}*/



	std::vector<VaoLayoutElement> layout = std::vector<VaoLayoutElement>();
	layout.push_back(VaoLayoutElement(FLOAT, 3, false));
	layout.push_back(VaoLayoutElement(FLOAT, 2, false));

	VBO* vbo = new VBO(cubeMesh.GetVertexData(), cubeMesh.GetVertexCount(), 5);
	VAO* vao = new VAO(vbo, layout);
	EBO* ebo = new EBO(cubeMesh.GetIndexData(), cubeMesh.GetIndexCount());
	int size = 0;

	//if (vbo->GetSize() / 4 != cubeMesh.GetIndexCount() / 6)
		//

	delete chunkMesh;
	chunkMesh = new Model(vao, ebo, glm::vec3(coordinates.x * CHUNK_DIMENSION, coordinates.y * CHUNK_DIMENSION, 
		coordinates.z * CHUNK_DIMENSION));
}

Block* Chunk::GetBlock(Coordinates coords)
{
	return &blocks[GetArrayPos(coords)];
}

inline int Chunk::GetArrayPos(int x, int y, int z)
{
	return x + CHUNK_DIMENSION * y + CHUNK_DIMENSION * CHUNK_DIMENSION * z;
}

inline int Chunk::GetArrayPos(Coordinates coord)
{
	return GetArrayPos(coord.x, coord.y, coord.z);
}

Chunk::Chunk(int inX, int inY, int inZ, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader)
{
	Chunk(Coordinates(inX, inY, inZ), atlas, chunkLoader);
}

Chunk::Chunk(Coordinates coord, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader)
{
	coordinates = coord;
	this->atlas = atlas;
	if (blockTypes == nullptr)
	{
		Chunk::AssignBlockTypes();
	}

	this->chunkLoader = chunkLoader;

	GenerateTerrain();
	GenerateChunkMesh();
}

Chunk::~Chunk() {
	delete chunkMesh;
	delete[] blocks;
}

void Chunk::Update()
{

}


Model* Chunk::GetChunkModel()
{
	return chunkMesh;
}

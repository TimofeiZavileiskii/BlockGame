#include "pch.h"
#include "Chunk.h"
#include "Model.h"
#include "CubeMeshCreator.h"
#include "Noise.h"
#include "ChunkLoader.h"
#include "Coordinates.h"
#include <iostream>

BlockType* Chunk::blockTypes;

void Chunk::GenerateTerrain()
{
	blocks = new Block[chunkSize];
	Noise noise = Noise();



	for (int i = 0; i < CHUNK_DIMENSION; i++) {
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++) {
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++) {
				int height = ii + CHUNK_DIMENSION * coordinates.y;
				int realX = i + coordinates.x * CHUNK_DIMENSION;
				int realZ = iii + coordinates.z * CHUNK_DIMENSION;
				
				float surface = 20.0f * noise.Sample(realX * 0.03f + 0.08f, realZ * 0.03f + 0.08f);

				if (height < surface){
					blocks[GetArrayPos(i, ii, iii)] = Block(&blockTypes[STONE]);
				}
				else if (height - 1 < surface){
					blocks[GetArrayPos(i, ii, iii)] = Block(&blockTypes[DIRT]);
				}
				else if (height - 2 < surface) {
					blocks[GetArrayPos(i, ii, iii)] = Block(&blockTypes[GRASS]);
				}
				else{
					blocks[GetArrayPos(i, ii, iii)] = Block(&blockTypes[AIR]);
				}
			}
		}
	}

}

void Chunk::FiniliseMesh()
{
	std::vector<VaoLayoutElement> layout = std::vector<VaoLayoutElement>();
	layout.push_back(VaoLayoutElement(FLOAT, 3, false));
	layout.push_back(VaoLayoutElement(FLOAT, 2, false));

	delete chunkMesh;

	if (meshCreator->GetVertexCount() != 0)
	{
		VBO* vbo = new VBO(meshCreator->GetVertexData(), meshCreator->GetVertexCount(), 5);
		VAO* vao = new VAO(vbo, layout);
		EBO* ebo = new EBO(meshCreator->GetIndexData(), meshCreator->GetIndexCount());

		chunkMesh = new Model(vao, ebo, glm::vec3(coordinates.x * CHUNK_DIMENSION, coordinates.y * CHUNK_DIMENSION,
			coordinates.z * CHUNK_DIMENSION));
	}
	else {
		chunkMesh = nullptr;
	}
	delete meshCreator;
	meshCreator = nullptr;
	state = FINISHED;
}

bool Chunk::NeedsFinilisation()
{
	return state == MODEL_GENERATED;
}

bool Chunk::IsUnprocessed()
{
	return state == UNROCESSED;
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

void Chunk::StartProccessing()
{
	state = WORKED_ON;
}

void Chunk::GenerateChunkMesh()
{
	meshCreator = new CubeMeshCreator(atlas);
	CubeMeshCreator& cubeMesh = *meshCreator;

	for (int i = 0; i < CHUNK_DIMENSION; i++)
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++)
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++)
				if (!blocks[GetArrayPos(i, ii, iii)].GetTransperency())
				{
					int arrayPos = GetArrayPos(i, ii, iii);
					
					if (ii - 1 < 0)
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
					else if(blocks[GetArrayPos(i, ii, iii - 1)].GetTransperency())
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
	state = MODEL_GENERATED;
}

Block* Chunk::GetBlock(Coordinates coords)
{
	return &blocks[GetArrayPos(coords)];
}

inline int Chunk::GetArrayPos(int x, int y, int z)
{
	return x + CHUNK_DIMENSION * y + CHUNK_DIMENSION * CHUNK_DIMENSION * z;
}

ChunkState Chunk::GetState()
{
	return state;
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

	state = UNROCESSED;
	chunkMesh = nullptr;
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

int Chunk::GetChunkDim()
{
	return CHUNK_DIMENSION;
}

Coordinates Chunk::GetCoordinates()
{
	return coordinates;
}

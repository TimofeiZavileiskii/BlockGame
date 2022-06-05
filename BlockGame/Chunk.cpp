#include "pch.h"
#include "Chunk.h"
#include "Model.h"
#include "CubeMeshCreator.h"
#include "Noise.h"
#include "ChunkLoader.h"
#include "Coordinates.h"
#include "LehmersRng.h"
#include <iostream>

BlockType* Chunk::blockTypes;

void Chunk::GenerateTerrain()
{
	blocks = new Block[chunkSize];
	Noise noise = Noise(worldSeed);

	LehmersRng rng = LehmersRng(worldSeed);
	float tempOffsetX = rng.intRandom() >> 5;
	float tempOffsetZ = rng.intRandom() >> 5;
	float humOffsetX = rng.intRandom() >> 5;
	float humOffsetZ = rng.intRandom() >> 5;

	for (int i = 0; i < CHUNK_DIMENSION; i++) {
		for (int iii = 0; iii < CHUNK_DIMENSION; iii++) {

			int realX = i + coordinates.x * CHUNK_DIMENSION;
			int realZ = iii + coordinates.z * CHUNK_DIMENSION;

			float nVal = noise.SampleOctaves(realX * 0.0003f, realZ * 0.0003f, 15, 0.5f);
			float surface = 1000.0f * std::pow(std::abs(nVal), 1.5f);
			if (nVal < 0) {
				surface = -surface;
			}

			float temperature = noise.SampleOctaves(realX * 0.0005f + tempOffsetX, realZ * 0.0005f + tempOffsetZ, 4, 0.5f);
			float humidity = noise.SampleOctaves(realX * 0.0005f + humOffsetX, realZ * 0.0005f + humOffsetZ, 4, 0.5f);

			for (int ii = 0; ii < CHUNK_DIMENSION; ii++) {

				int height = ii + CHUNK_DIMENSION * coordinates.y;

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
	state = TERRAIN_GENERATED;
}

void Chunk::FiniliseMesh()
{
	std::vector<VaoLayoutElement> layout = std::vector<VaoLayoutElement>();
	layout.push_back(VaoLayoutElement(FLOAT, 3, false));  //Coordinates
	layout.push_back(VaoLayoutElement(FLOAT, 2, false));  //Texture coordinates

	delete chunkMesh;

	if (meshCreator->GetVertexCount() != 0)
	{
		VBO* vbo = new VBO(meshCreator->GetVertexData(), meshCreator->GetVertexCount(), 3+2);
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

void Chunk::AssignBlockTypes()
{
	blockTypes = new BlockType[BLOCK_ID_LENGTH];

	blockTypes[AIR]   = BlockType(true, "");
	blockTypes[STONE] = BlockType(false, "Stone");
	blockTypes[SAND]  = BlockType(false, "Sand");
	blockTypes[DIRT]  = BlockType(false, "Dirt");
	blockTypes[BRICK] = BlockType(false, "Bricks");
	blockTypes[GRASS] = BlockType(false, "Grass");
	blockTypes[COBLESTONE] = BlockType(false, "Coblestone");
	blockTypes[SANDSTONE] = BlockType(false, "Sandstone");
	blockTypes[DIRT_JUNGLE] = BlockType(false, "DirtJungle");
	blockTypes[GRASS_JUNGLE] = BlockType(false, "GrassJungle");
}

void Chunk::StartProccessingTerrain()
{
	state = TERRAIN_WORKED_ON;
}

void Chunk::GenerateChunkMesh()
{
	meshCreator = new CubeMeshCreator(atlas);
	CubeMeshCreator& cubeMesh = *meshCreator;

	Chunk* leftChunk   = chunkLoader->GetChunk(coordinates.x - 1, coordinates.y, coordinates.z);
	Chunk* rightChunk  = chunkLoader->GetChunk(coordinates.x + 1, coordinates.y, coordinates.z);
	Chunk* frontChunk  = chunkLoader->GetChunk(coordinates.x, coordinates.y, coordinates.z + 1);
	Chunk* backChunk   = chunkLoader->GetChunk(coordinates.x, coordinates.y, coordinates.z - 1);
	Chunk* topChunk    = chunkLoader->GetChunk(coordinates.x, coordinates.y + 1, coordinates.z);
	Chunk* bottomChunk = chunkLoader->GetChunk(coordinates.x, coordinates.y - 1, coordinates.z);

	for (int i = 0; i < CHUNK_DIMENSION; i++)
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++)
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++){
				if (!blocks[GetArrayPos(i, ii, iii)].GetTransperency())
				{
					int arrayPos = GetArrayPos(i, ii, iii);

					if (ii - 1 < 0)
					{
						if (bottomChunk->GetBlock(Coordinates(i, CHUNK_DIMENSION - 1, iii))->GetTransperency())
							cubeMesh.AddBottomFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii - 1, iii)].GetTransperency())
					{
						cubeMesh.AddBottomFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (ii + 1 > CHUNK_DIMENSION - 1)
					{
						if (topChunk->GetBlock(Coordinates(i, 0, iii))->GetTransperency())
							cubeMesh.AddTopFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii + 1, iii)].GetTransperency())
					{
						cubeMesh.AddTopFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (i - 1 < 0)
					{
						if (leftChunk->GetBlock(Coordinates(CHUNK_DIMENSION - 1, ii, iii))->GetTransperency())
							cubeMesh.AddLeftFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i - 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddLeftFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (i + 1 > CHUNK_DIMENSION - 1)
					{
						if (rightChunk->GetBlock(Coordinates(0, ii, iii))->GetTransperency())
							cubeMesh.AddRightFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i + 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddRightFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (iii - 1 < 0)
					{
						if (backChunk->GetBlock(Coordinates(i, ii, CHUNK_DIMENSION - 1))->GetTransperency())
							cubeMesh.AddFrontFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii, iii - 1)].GetTransperency())
					{
						cubeMesh.AddFrontFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (iii + 1 > CHUNK_DIMENSION - 1)
					{
						if (frontChunk->GetBlock(Coordinates(i, ii, 0))->GetTransperency())
							cubeMesh.AddBackFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
					else if (blocks[GetArrayPos(i, ii, iii + 1)].GetTransperency())
					{
						cubeMesh.AddBackFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
				}
			}
	state = MODEL_GENERATED;
}

Block* Chunk::GetBlock(Coordinates coords)
{
	return &blocks[GetArrayPos(coords)];
}

Block* Chunk::GetBlock(int x, int y, int z) 
{
	return GetBlock(Coordinates(x, y, z));
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

Chunk::Chunk(int inX, int inY, int inZ, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader, int worldSeed)
{
	Chunk(Coordinates(inX, inY, inZ), atlas, chunkLoader, worldSeed);
}

Chunk::Chunk(Coordinates coord, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader, int worldSeed)
{
	coordinates = coord;
	this->worldSeed = worldSeed;
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

void Chunk::StartProccessingModel() {
	state = MODEL_WORKED_ON;
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

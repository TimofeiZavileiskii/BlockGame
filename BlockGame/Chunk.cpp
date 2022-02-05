#include "pch.h"
#include "Chunk.h"
#include "Model.h"
#include "CubeMeshCreator.h"
#include "PerlinNoise.h"

BlockType* Chunk::blockTypes;

void Chunk::GenerateTerrain()
{
	blocks = new Block[chunkSize];
	PerlinNoise noise = PerlinNoise();

	for (int i = 0; i < CHUNK_DIMENSION; i++) {
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++) {
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++) {
				
				float height = ((float)(ii + CHUNK_DIMENSION * coordinates.y) + 0.01) / (float)40;
				float x = ((float)(i + CHUNK_DIMENSION * coordinates.x) + 0.01) / (float)40;
				float y = ((float)(iii + CHUNK_DIMENSION * coordinates.z) + 0.01) / (float)40;
				if (height <  0.2 * (sin(x * 5) + sin(y * 5))) 
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

	for (int i = 0; i < CHUNK_DIMENSION; i++)
	{
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++)
		{
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++)
			{
				if (!blocks[GetArrayPos(i, ii, iii)].GetTransperency())
				{
					int arrayPos = GetArrayPos(i, ii, iii);
					if (ii - 1 < 0 || blocks[GetArrayPos(i, ii - 1, iii)].GetTransperency())
					{
						cubeMesh.AddBottomFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (ii + 1 > CHUNK_DIMENSION - 1 || blocks[GetArrayPos(i, ii + 1, iii)].GetTransperency())
					{
						cubeMesh.AddTopFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (i - 1 < 0 || blocks[GetArrayPos(i - 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddLeftFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (i + 1 > CHUNK_DIMENSION - 1 || blocks[GetArrayPos(i + 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddRightFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (iii - 1 < 0 || blocks[GetArrayPos(i, ii, iii - 1)].GetTransperency())
					{
						cubeMesh.AddFrontFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}

					if (iii + 1 > CHUNK_DIMENSION - 1 || blocks[GetArrayPos(i, ii, iii + 1)].GetTransperency())
					{
						cubeMesh.AddBackFace(i, ii, iii, blocks[arrayPos].GetTexture());
					}
				}
			}
		}
	}

	std::vector<VaoLayoutElement> layout = std::vector<VaoLayoutElement>();
	layout.push_back(VaoLayoutElement(FLOAT, 3, false));
	layout.push_back(VaoLayoutElement(FLOAT, 2, false));

	VBO* vbo = new VBO(cubeMesh.GetVertexData(), cubeMesh.GetVertexCount(), 5);
	VAO* vao = new VAO(vbo, layout);
	EBO* ebo = new EBO(cubeMesh.GetIndexData(), cubeMesh.GetIndexCount());

	delete chunkMesh;
	chunkMesh = new Model(vao, ebo, glm::vec3(coordinates.x * CHUNK_DIMENSION, coordinates.y * CHUNK_DIMENSION, 
		coordinates.z * CHUNK_DIMENSION));
}

inline int Chunk::GetArrayPos(int x, int y, int z)
{
	return x + CHUNK_DIMENSION * y + CHUNK_DIMENSION * CHUNK_DIMENSION * z;
}

inline int Chunk::GetArrayPos(Coordinates coord)
{
	GetArrayPos(coord.x, coord.y, coord.z);
}

Chunk::Chunk(int inX, int inY, int inZ, BlockTextureAtlas* atlas)
{
	Chunk(Coordinates(inX, inY, inZ), atlas);
}

Chunk::Chunk(Coordinates coord, BlockTextureAtlas* atlas)
{
	coordinates = coord;
	this->atlas = atlas;
	if (blockTypes == nullptr)
	{
		Chunk::AssignBlockTypes();
	}

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

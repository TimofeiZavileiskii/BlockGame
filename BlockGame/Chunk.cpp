#include "pch.h"
#include "Chunk.h"
#include "Model.h"
#include "CubeMeshCreator.h"

BlockType* Chunk::blockTypes;

void Chunk::GenerateTerrain()
{
	blocks = new Block[chunkSize];

	for (int i = 0; i < CHUNK_DIMENSION; i++) {
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++) {
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++) {
				if (ii < CHUNK_DIMENSION / 2)
				{
					blocks[GetCoord(i, ii, iii)] = Block(&blockTypes[STONE]);
				}
				else
				{
					blocks[GetCoord(i, ii, iii)] = Block(&blockTypes[AIR]);
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
}

void Chunk::GenerateChunkMesh()
{
	CubeMeshCreator cubeMesh = CubeMeshCreator();

	for (int i = 0; i < CHUNK_DIMENSION; i++)
	{
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++)
		{
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++)
			{
				if (!blocks[GetCoord(i, ii, iii)].GetTransperency())
				{
					if (ii - 1 < 0)
					{
						cubeMesh.AddFrontFace(i, ii, iii);
					}
					else if (blocks[GetCoord(i, ii - 1, iii)].GetTransperency())
					{
						cubeMesh.AddFrontFace(i, ii, iii);
					}

					if (iii + 2 > CHUNK_DIMENSION)
					{
						cubeMesh.AddTopFace(i, ii, iii);
					}
					else if (blocks[GetCoord(i, ii, iii + 1)].GetTransperency())
					{
						cubeMesh.AddTopFace(i, ii, iii);
					}

					if (i - 1 < 0)
					{
						cubeMesh.AddLeftFace(i, ii, iii);
					}
					else if (blocks[GetCoord(i - 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddLeftFace(i, ii, iii);
					}

					if (i + 2 > CHUNK_DIMENSION)
					{
						cubeMesh.AddRightFace(i, ii, iii);
					}
					else if (blocks[GetCoord(i + 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddRightFace(i, ii, iii);
					}

					if (iii - 1 < 0)
					{
						cubeMesh.AddBottomFace(i, ii, iii);
					}
					else if (blocks[GetCoord(i, ii, iii - 1)].GetTransperency())
					{
						cubeMesh.AddBottomFace(i, ii, iii);
					}

					//Add back face
					if (ii + 2 > CHUNK_DIMENSION)
					{
						cubeMesh.AddBackFace(i, ii, iii);
					}
					else if (blocks[GetCoord(i, ii + 1, iii)].GetTransperency())
					{
						cubeMesh.AddBackFace(i, ii, iii);
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
	chunkMesh = new Model(vao, ebo, glm::vec3(0.0f));
}

inline int Chunk::GetCoord(int x, int y, int z)
{
	return x + CHUNK_DIMENSION * y + CHUNK_DIMENSION * CHUNK_DIMENSION * z;;
}

Chunk::Chunk()
{
	if (blockTypes == nullptr) 
	{
		Chunk::AssignBlockTypes();
	}

	GenerateTerrain();
	GenerateChunkMesh();
}

void Chunk::Update()
{
}

Model* Chunk::GetChunkModel()
{
	return chunkMesh;
}

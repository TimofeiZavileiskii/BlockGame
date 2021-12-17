#include "pch.h"
#include "World.h"
#include "Window.h"
#include "CubeMeshCreator.h"
#include <random>

void World::FillBlockData()
{
	blockTypes = new BlockType[BLOCK_ID_LENGTH];

	blockTypes[AIR] = BlockType(true, "");
	blockTypes[STONE] = BlockType(false, "Stone");
}

void World::AssignBlockTypes()
{
	blockData = new Block[chunkSize];

	for(int i = 0; i < CHUNK_DIMENSION; i++){
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++){
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++){
				if (ii < CHUNK_DIMENSION / 2)
				{
					blockData[GetCoord(i, ii, iii)] = Block(&blockTypes[STONE]);
				}
				else
				{
					blockData[GetCoord(i, ii, iii)] = Block(&blockTypes[AIR]);
				}
			}		
		}		
	}
}

void World::UpdateCamera()
{
	float rotationSpeed = 50.0f * window->GetTime();
	glm::vec2 offset = window->GetCursorOffset();
	camera->Rotate(glm::vec2(offset.x *= rotationSpeed, offset.y *= rotationSpeed));

	if (window->GetInput(W))
		camera->Move(window->GetTime());
	if (window->GetInput(S))
		camera->Move(-window->GetTime());
	if (window->GetInput(D))
		camera->Strafe(window->GetTime());
	if (window->GetInput(A))
		camera->Strafe(-window->GetTime());

}

void World::GenerateChunkMesh()
{
	CubeMeshCreator cubeMesh = CubeMeshCreator();

	for (int i = 0; i < CHUNK_DIMENSION; i++) 
	{
		for (int ii = 0; ii < CHUNK_DIMENSION; ii++) 
		{
			for (int iii = 0; iii < CHUNK_DIMENSION; iii++) 
			{
				if (!blockData[GetCoord(i, ii, iii)].GetTransperency()) 
				{
					if (ii - 1 < 0) 
					{
						cubeMesh.AddFrontFace(i, ii, iii);
					}
					else if (blockData[GetCoord(i, ii - 1, iii)].GetTransperency())
					{
						cubeMesh.AddFrontFace(i, ii, iii);
					}

					if (iii + 2 > CHUNK_DIMENSION) 
					{
						cubeMesh.AddTopFace(i, ii, iii);
					}
					else if (blockData[GetCoord(i, ii, iii + 1)].GetTransperency())
					{
						cubeMesh.AddTopFace(i, ii, iii);
					}

					if (i - 1 < 0)
					{
						cubeMesh.AddLeftFace(i, ii, iii);
					}
					else if (blockData[GetCoord(i - 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddLeftFace(i, ii, iii);
					}

					if (i + 2 > CHUNK_DIMENSION) 
					{
						cubeMesh.AddRightFace(i, ii, iii);
					}
					else if (blockData[GetCoord(i + 1, ii, iii)].GetTransperency())
					{
						cubeMesh.AddRightFace(i, ii, iii);
					}

					if (iii - 1 < 0) 
					{
						cubeMesh.AddBottomFace(i, ii, iii);
					}
					else if (blockData[GetCoord(i, ii, iii - 1)].GetTransperency())
					{
						cubeMesh.AddBottomFace(i, ii, iii);
					}

					//Add back face
					if (ii + 2 > CHUNK_DIMENSION) 
					{
						cubeMesh.AddBackFace(i, ii, iii);
					}
					else if (blockData[GetCoord(i, ii + 1, iii)].GetTransperency())
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

	delete worldMesh;
	worldMesh = new Model(vao, ebo);
}

inline int World::GetCoord(int x, int y, int z)
{
	return x + CHUNK_DIMENSION * y + CHUNK_DIMENSION * CHUNK_DIMENSION * z;
}


World::World(Window* inWindow)
{
	window = inWindow;
	camera = new Camera(glm::vec3(0.0f, 40.0f, 20.0f), glm::vec2(0.0f, 0.0f), 70.0f, window->GetAspectRation());
	worldMesh = nullptr;

	FillBlockData();
	AssignBlockTypes();
	GenerateChunkMesh();

	Update();
}

void World::Update()
{

	passedTime = window->GetTime();

	UpdateCamera();
}

Camera* World::GetCamera()
{
	return camera;
}

Model* World::GetChunkMesh()
{
	return worldMesh;
}

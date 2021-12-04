#pragma once
#include <glm/vec3.hpp>

class Entity
{
private:
	glm::vec3 position;

public:
	Entity(glm::vec3 inPosition);

	glm::vec3 GetPosition();

	void SetPosition(glm::vec3 inPosition);
};


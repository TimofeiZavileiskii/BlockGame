#include "pch.h"
#include "Entity.h"

glm::vec3 Entity::GetPosition() 
{
	return position;
}

Entity::Entity(glm::vec3 inPosition)
{
	position = inPosition;
}

void Entity::SetPosition(glm::vec3 inPosition) 
{
	position = inPosition;
}
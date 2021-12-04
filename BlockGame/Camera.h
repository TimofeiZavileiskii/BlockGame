#pragma once
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Entity.h"
#include "ErrorLoger.h"

class Camera : public Entity
{
private:
	float fov;
	float aspectRatio;
	float speed;

	glm::vec3 cameraFront;
	glm::vec2 rotation;
	glm::vec3 up;

	void SetCameraFront();

public:
	Camera(glm::vec3 inPosition, glm::vec2 inRotation, float inFov, float inAspectRatio);

	void Rotate(glm::vec2 rotationChange);

	glm::mat4 GetViewMatrix();

	glm::mat4 GetPerspectiveMatrix();

	void Move(float scalar);

	void Strafe(float scalar);
};


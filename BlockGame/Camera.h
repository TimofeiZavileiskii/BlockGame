#pragma once
#include "Entity.h"
#include "ErrorLoger.h"
#include <glm/mat4x4.hpp>

class Camera : public Entity
{
private:
	float fov;
	float aspectRatio;
	float speed;
	float viewDistance;
	float nearDistance;

	glm::vec3 cameraFront;
	glm::vec2 rotation;
	glm::vec3 up;

	void SetCameraFront();

public:
	Camera(glm::vec3 inPosition, glm::vec2 inRotation, float inFov, float inAspectRatio);

	float GetFov();

	float GetAspectRatio();

	float GetViewDistance();

	float GetNearDistance();

	glm::vec3 GetDirection();

	void Rotate(glm::vec2 rotationChange);

	glm::mat4 GetViewMatrix();

	glm::mat4 GetPerspectiveMatrix();

	void Move(float scalar);

	void Strafe(float scalar);
};


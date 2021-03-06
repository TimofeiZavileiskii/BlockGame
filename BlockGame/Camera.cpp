#include "pch.h"
#include "Camera.h"

void Camera::SetCameraFront() 
{
    glm::vec3 direction;

    direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    direction.y = sin(glm::radians(rotation.y));
    direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

    cameraFront = glm::normalize(direction);
}

Camera::Camera(glm::vec3 inPosition, glm::vec2 inRotation, float inFov, float inAspectRatio) : Entity(inPosition)
{
	fov = inFov;
    aspectRatio = inAspectRatio;
    speed = 100.00f;
    viewDistance = 500.0f;
    nearDistance = 0.1f;

    rotation = inRotation;

    up = glm::vec3(0.0f, 1.0f, 0.0f);

    SetCameraFront();
}

float Camera::GetFov()
{
    return fov;
}

float Camera::GetAspectRatio()
{
    return aspectRatio;
}

float Camera::GetViewDistance()
{
    return viewDistance;
}

float Camera::GetNearDistance()
{
    return nearDistance;
}

glm::vec3 Camera::GetDirection()
{
    return cameraFront;
}

void Camera::Move(float scalar)
{
    glm::vec3 position = GetPosition();

    position += cameraFront * speed * scalar;
    SetPosition(position);
}

void Camera::Strafe(float scalar) 
{
    glm::vec3 position = GetPosition();

    position += scalar * speed * glm::normalize(glm::cross(cameraFront, up));
    SetPosition(position);
}

void Camera::Rotate(glm::vec2 rotationChange) 
{
    rotation.x -= rotationChange.x;
    rotation.y += rotationChange.y;

    if (rotation.y > 89.0f)
        rotation.y = 89.0f;
    if (rotation.y < -89.0f)
        rotation.y = -89.0f;

    SetCameraFront();

    ErrorLoger* errorLoger = errorLoger->instance();
}

glm::mat4 Camera::GetViewMatrix() 
{
    glm::mat4 viewMat = glm::lookAt(GetPosition(), GetPosition() + cameraFront, up);

    return viewMat;
}

glm::mat4 Camera::GetPerspectiveMatrix() 
{
    glm::mat4 projMat = glm::perspective(glm::radians(fov), aspectRatio, nearDistance, viewDistance);
    
    return projMat;
}
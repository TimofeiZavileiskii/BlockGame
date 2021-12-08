#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"

class Shader
{
private:
	unsigned int ID;

public:
	Shader(const char* vertexShader, const char* fragmentShader);

	void Bind() const;

	void SetUniformMatf4(const std::string& name, const glm::mat4& matrix);
};


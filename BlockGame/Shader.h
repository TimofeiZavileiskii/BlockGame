#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int ID;

public:
	Shader(const char* vertexShader, const char* fragmentShader);

	void Bind();

	void SetUniformMatf4(std::string name, glm::mat4 matrix);
};


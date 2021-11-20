#pragma once
#include <glad/glad.h>

class Shader
{
private:
	unsigned int ID;

public:
	Shader(const char* vertexShader, const char* fragmentShader);

	void Bind();
};


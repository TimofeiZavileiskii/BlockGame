#include "Shader.h"

Shader::Shader(const char* vertShaderSource, const char* fragShaderSource) 
{
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertShaderSource, 0);
    glCompileShader(vertShader);

    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, 0);
    glCompileShader(fragShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}


void Shader::Bind() const
{
    glUseProgram(ID);
}

void Shader::SetUniformMatf4(std::string name, glm::mat4 matrix)
{
    int uniformId = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(matrix));
}

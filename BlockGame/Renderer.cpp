#include "pch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <glfw3.h>
#include "DataManager.h"
#include "ErrorLoger.h"
#include "Camera.h"

Renderer::Renderer(int inWidth, int inHeight) 
{
    errorTitle = "Renderer";
    width = inWidth;
    height = inHeight;

    errorLoger = errorLoger->instance();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        errorLoger->PushError(errorTitle, "Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glClearColor(0.65f, 0.90f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    dataManager = new DataManager();
}

void Renderer::ProcessErrors() 
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  
            error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 
            error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             
            error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                
            error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               
            error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 
            error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: 
            error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }

        errorLoger->PushError(errorTitle, error);
       // errorLoger->PushError(errorTitle, (int)errorCode);
    }
}

void Renderer::Draw(Camera* camera, std::vector<Model*> chunks)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* shader = dataManager->GetShader("Test");
    shader->Bind();
    shader->SetUniformMatf4("view", camera->GetViewMatrix());
    shader->SetUniformMatf4("projection", camera->GetPerspectiveMatrix());
    dataManager->GetTexture("Stone")->Bind();

    for (Model* model : chunks) 
    {
        model->Bind();
        shader->SetUniformMatf4("model", glm::translate(glm::mat4(1.0f), model->GetPosition()));

        model->Draw();
    }


    ProcessErrors();
}

#include "Renderer.h"

Renderer::Renderer(int width, int height) 
{
    errorTitle = "Renderer";

    errorLoger = errorLoger->instance();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        errorLoger->PushError(errorTitle, "Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glClearColor(0.3f, 0.2f, 0.2f, 1.0f);

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
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }

        errorLoger->PushError(errorTitle, error);
    }
}

void Renderer::Draw() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    dataManager->GetMesh("test")->Bind();
    dataManager->GetShader("test")->Bind();
   

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    ProcessErrors();
}

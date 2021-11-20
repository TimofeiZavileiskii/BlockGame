#include "Window.h"

Window::Window(int inWidth, int inHeight, std::string inTitle) 
{
        errorTitle = "Window";

        width = inWidth;
        height = inHeight;
        title = inTitle;

        errorLoger = errorLoger->instance();

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpengGLVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpengGLVersionMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (window == NULL)
        {
            errorLoger->PushError(errorTitle, "Window has failed to be created");
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        inputManager = new InputManager(window);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::ProcessInputs() 
{
    glfwPollEvents();
}

void Window::Update() 
{
    glfwSwapBuffers(window);
}

bool Window::GetInput(KeyCodes key)
{
    return inputManager->GetInput(key);
}
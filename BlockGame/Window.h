#pragma once
#include <glfw3.h>
#include "ErrorLoger.h"
#include "InputManager.h"

class Window
{
private:
    const int OpengGLVersionMajor = 4;
    const int OpengGLVersionMinor = 6;


	int width;
	int height;
    std::string title;
    std::string errorTitle;

	GLFWwindow* window;
    InputManager* inputManager;

    ErrorLoger* errorLoger;

public:
    Window(int inWidth, int inHeight, std::string inTitle);

    ~Window();

    void Update();

    void ProcessInputs();

    bool GetInput(KeyCodes key);
};


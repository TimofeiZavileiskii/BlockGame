#pragma once
#include "InputManager.h"

struct GLFWwindow;
class InputManager;
class ErrorLoger;

class Window
{
private:
    const int OpengGLVersionMajor = 4;
    const int OpengGLVersionMinor = 6;

    GLFWwindow* window;
    InputManager* inputManager;
    ErrorLoger* errorLoger;

	int width;
	int height;

    std::string title;
    std::string errorTitle;

    double passedTime;
    double lastFrameTime;

    void UpdateTime();

public:
    Window(int inWidth, int inHeight, std::string inTitle);

    ~Window();

    void Update();

    void ProcessEvents();

    bool GetInput(KeyCodes key);

    glm::dvec2 GetCursorOffset();

    double GetTime();
    
    float GetAspectRation();
};


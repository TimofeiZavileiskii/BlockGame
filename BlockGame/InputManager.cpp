#include "InputManager.h"


InputManager::InputManager(GLFWwindow* inWindow, int width, int height)
{
	window = inWindow;

	windowWidth = width;
	windowHeight = height;


	//I know it is horrible
	glfwKeys = new int[(int)KeyCodes::NUMBER_OF_KEY_CODES];

	glfwKeys[(int)KeyCodes::Q] = GLFW_KEY_Q;
	glfwKeys[(int)KeyCodes::W] = GLFW_KEY_W;
	glfwKeys[(int)KeyCodes::E] = GLFW_KEY_E;
	glfwKeys[(int)KeyCodes::R] = GLFW_KEY_R;
	glfwKeys[(int)KeyCodes::T] = GLFW_KEY_T;
	glfwKeys[(int)KeyCodes::Y] = GLFW_KEY_Y;
	glfwKeys[(int)KeyCodes::U] = GLFW_KEY_U;
	glfwKeys[(int)KeyCodes::I] = GLFW_KEY_I;
	glfwKeys[(int)KeyCodes::O] = GLFW_KEY_O;
	glfwKeys[(int)KeyCodes::P] = GLFW_KEY_P;
	glfwKeys[(int)KeyCodes::A] = GLFW_KEY_A;
	glfwKeys[(int)KeyCodes::S] = GLFW_KEY_S;
	glfwKeys[(int)KeyCodes::D] = GLFW_KEY_D;
	glfwKeys[(int)KeyCodes::F] = GLFW_KEY_F;
	glfwKeys[(int)KeyCodes::G] = GLFW_KEY_G;
	glfwKeys[(int)KeyCodes::H] = GLFW_KEY_H;
	glfwKeys[(int)KeyCodes::J] = GLFW_KEY_J;
	glfwKeys[(int)KeyCodes::K] = GLFW_KEY_K;
	glfwKeys[(int)KeyCodes::L] = GLFW_KEY_L;
	glfwKeys[(int)KeyCodes::Z] = GLFW_KEY_Z;
	glfwKeys[(int)KeyCodes::X] = GLFW_KEY_X;
	glfwKeys[(int)KeyCodes::C] = GLFW_KEY_C;
	glfwKeys[(int)KeyCodes::V] = GLFW_KEY_V;
	glfwKeys[(int)KeyCodes::B] = GLFW_KEY_B;
	glfwKeys[(int)KeyCodes::N] = GLFW_KEY_N;
	glfwKeys[(int)KeyCodes::M] = GLFW_KEY_M;
	glfwKeys[(int)KeyCodes::_1] = GLFW_KEY_1;
	glfwKeys[(int)KeyCodes::_2] = GLFW_KEY_2;
	glfwKeys[(int)KeyCodes::_3] = GLFW_KEY_3;
	glfwKeys[(int)KeyCodes::_4] = GLFW_KEY_4;
	glfwKeys[(int)KeyCodes::_5] = GLFW_KEY_5;
	glfwKeys[(int)KeyCodes::_6] = GLFW_KEY_6;
	glfwKeys[(int)KeyCodes::_7] = GLFW_KEY_7;
	glfwKeys[(int)KeyCodes::_8] = GLFW_KEY_8;
	glfwKeys[(int)KeyCodes::_9] = GLFW_KEY_9;
	glfwKeys[(int)KeyCodes::_0] = GLFW_KEY_0;
	glfwKeys[(int)KeyCodes::ESC] = GLFW_KEY_ESCAPE;
	glfwKeys[(int)KeyCodes::SHIFT] = GLFW_KEY_LEFT_SHIFT;
	glfwKeys[(int)KeyCodes::CTRL] = GLFW_KEY_LEFT_CONTROL;
	glfwKeys[(int)KeyCodes::CAPS_LOCK] = GLFW_KEY_CAPS_LOCK;
	glfwKeys[(int)KeyCodes::TAB] = GLFW_KEY_TAB;
			 
	glfwKeys[(int)KeyCodes::LEFT_MOUSE] = GLFW_MOUSE_BUTTON_1;
	glfwKeys[(int)KeyCodes::RIGHT_MOUSE] = GLFW_MOUSE_BUTTON_2;
}

bool InputManager::GetInput(KeyCodes checkedKey)
{
	int glfwKey = glfwKeys[checkedKey];
	bool output;

	if (checkedKey < LEFT_MOUSE) 
	{
		output = (glfwGetKey(window, glfwKey) == GLFW_PRESS);
	}
	else 
	{
		output = (glfwGetMouseButton(window, glfwKey) == GLFW_PRESS);
	}

	return output;
}

void InputManager::UpdateCursorPos() 
{
	double PosX, PosY;

	glfwGetCursorPos(window, &PosX, &PosY);


	CursorOffset = glm::dvec2(windowWidth / 2 - CursorPos.x, windowHeight / 2 - CursorPos.y);
	glfwSetCursorPos(window, windowWidth / 2, windowHeight /2);
	CursorPos = glm::dvec2(PosX, PosY);
}

glm::dvec2 InputManager::GetCursorPosition() 
{
	return CursorPos;
}

glm::dvec2 InputManager::GetCursorOffset() 
{
	return CursorOffset;
}
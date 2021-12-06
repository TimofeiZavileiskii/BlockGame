#include "InputManager.h"


InputManager::InputManager(GLFWwindow* inWindow, int width, int height)
{
	window = inWindow;

	windowWidth = width;
	windowHeight = height;


	//I know it is horrible
	glfwKeys = new int[NUMBER_OF_KEY_CODES];

	glfwKeys[Q] = GLFW_KEY_Q;
	glfwKeys[W] = GLFW_KEY_W;
	glfwKeys[E] = GLFW_KEY_E;
	glfwKeys[R] = GLFW_KEY_R;
	glfwKeys[T] = GLFW_KEY_T;
	glfwKeys[Y] = GLFW_KEY_Y;
	glfwKeys[U] = GLFW_KEY_U;
	glfwKeys[I] = GLFW_KEY_I;
	glfwKeys[O] = GLFW_KEY_O;
	glfwKeys[P] = GLFW_KEY_P;
	glfwKeys[A] = GLFW_KEY_A;
	glfwKeys[S] = GLFW_KEY_S;
	glfwKeys[D] = GLFW_KEY_D;
	glfwKeys[F] = GLFW_KEY_F;
	glfwKeys[G] = GLFW_KEY_G;
	glfwKeys[H] = GLFW_KEY_H;
	glfwKeys[J] = GLFW_KEY_J;
	glfwKeys[K] = GLFW_KEY_K;
	glfwKeys[L] = GLFW_KEY_L;
	glfwKeys[Z] = GLFW_KEY_Z;
	glfwKeys[X] = GLFW_KEY_X;
	glfwKeys[C] = GLFW_KEY_C;
	glfwKeys[V] = GLFW_KEY_V;
	glfwKeys[B] = GLFW_KEY_B;
	glfwKeys[N] = GLFW_KEY_N;
	glfwKeys[M] = GLFW_KEY_M;
	glfwKeys[_1] = GLFW_KEY_1;
	glfwKeys[_2] = GLFW_KEY_2;
	glfwKeys[_3] = GLFW_KEY_3;
	glfwKeys[_4] = GLFW_KEY_4;
	glfwKeys[_5] = GLFW_KEY_5;
	glfwKeys[_6] = GLFW_KEY_6;
	glfwKeys[_7] = GLFW_KEY_7;
	glfwKeys[_8] = GLFW_KEY_8;
	glfwKeys[_9] = GLFW_KEY_9;
	glfwKeys[_0] = GLFW_KEY_0;
	glfwKeys[ESC] = GLFW_KEY_ESCAPE;
	glfwKeys[SHIFT] = GLFW_KEY_LEFT_SHIFT;
	glfwKeys[CTRL] = GLFW_KEY_LEFT_CONTROL;
	glfwKeys[CAPS_LOCK] = GLFW_KEY_CAPS_LOCK;
	glfwKeys[TAB] = GLFW_KEY_TAB;

	glfwKeys[LEFT_MOUSE] = GLFW_MOUSE_BUTTON_1;
	glfwKeys[RIGHT_MOUSE] = GLFW_MOUSE_BUTTON_2;
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
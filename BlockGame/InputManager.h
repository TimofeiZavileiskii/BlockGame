#pragma once
#include <glfw3.h>

enum KeyCodes
{
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L, Z, X,
	C, V, B, N, M,
	_1, _2, _3, _4, _5, _6, _7, _8, _9, _0,
	ESC, SHIFT, CTRL, CAPS_LOCK, TAB,
	NUMBER_OF_KEY_CODES
};

class InputManager
{
	GLFWwindow* window;
	int* glfwKeys;

public:
	InputManager(GLFWwindow* inWindow);
	
	bool GetInput(KeyCodes checkedKey);

};


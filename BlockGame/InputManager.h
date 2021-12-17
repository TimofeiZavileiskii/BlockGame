#pragma once
#include <glm/vec2.hpp>

enum KeyCodes
{
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L, Z, X,
	C, V, B, N, M,
	_1, _2, _3, _4, _5, _6, _7, _8, _9, _0,
	ESC, SHIFT, CTRL, CAPS_LOCK, TAB,
	LEFT_MOUSE, RIGHT_MOUSE,
	NUMBER_OF_KEY_CODES
};

struct GLFWwindow;

class InputManager
{
	GLFWwindow* window;
	int* glfwKeys;
	int windowWidth;
	int windowHeight;

	glm::dvec2 CursorPos;
	glm::dvec2 CursorOffset;

public:
	InputManager(GLFWwindow* inWindow, int width, int height);
	
	bool GetInput(KeyCodes checkedKey);

	void UpdateCursorPos();

	glm::dvec2 GetCursorPosition();

	glm::dvec2 GetCursorOffset();
};


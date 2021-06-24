#include <V5/Core/Input.h>
#include <GLFW/glfw3.h>
#include "CoreLogger.h"

using namespace V5Core;

bool Input::s_keyDown[MAX_KEYS];
bool Input::s_keyHold[MAX_KEYS];
bool Input::s_mouseDown[MAX_KEYS];
bool Input::s_mouseHold[MAX_KEYS];


std::array<double, 2> Input::s_mousePosition;


void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		s_keyDown[key] = 1;
		s_keyHold[key] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
		s_keyDown[key] = 0;
		s_keyHold[key] = 0;
	}	
}

bool Input::IsKeyDown(int key) { return s_keyDown[key]; };
bool Input::IsKeyHold(int key) { return s_keyHold[key]; };
bool Input::IsMouseButtonDown(int key) { return s_mouseDown[key]; }
bool Input::IsMouseButtonHold(int key) { return s_mouseHold[key]; }

void Input::MouseCallback(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		s_mouseDown[key] = 1;
		s_mouseHold[key] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
		s_mouseDown[key] = 0;
		s_mouseHold[key] = 0;
	}
}

std::array<double, 2>& Input::GetMousePosition()
{
	return s_mousePosition;
}


void Input::UpdateMousePos(double x, double y)
{
	s_mousePosition[0] = x;
	s_mousePosition[1] = y;
}


void Input::ResetDownKeys()
{
	memset(s_keyDown, 0, MAX_KEYS);
	memset(s_mouseDown, 0, MAX_BUTTONS);
}

#pragma once

#include "../Dll.h"
#include <GLFW/glfw3.h>
#include "KeyCodes.h"
#include <array>

#define MAX_KEYS 500
#define MAX_BUTTONS 20

namespace V5Core
{
	class V5_API Input
	{

	public:
		friend class Window;
		friend class Core;

		static bool IsKeyDown(int key);
		static bool IsKeyHold(int key);

		static bool IsMouseButtonDown(int key);
		static bool IsMouseButtonHold(int key);
		static std::array<double, 2>& GetMousePosition();

	private:
		static void UpdateMousePos(double x, double y);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(int key, int action);
		static void ResetDownKeys();


		static bool s_keyDown[MAX_KEYS];
		static bool s_keyHold[MAX_KEYS];

		static bool s_mouseDown[MAX_KEYS];
		static bool s_mouseHold[MAX_KEYS];
		static std::array<double, 2> s_mousePosition;
	};
}

#pragma once

#include <V5/Core/PlatformDetection.h>
#include "KeyCodes.h"
#include <array>

#ifdef V5_PLATFORM_WINDOWS
#include <GLFW/glfw3.h>
#endif

#define MAX_KEYS 500
#define MAX_BUTTONS 20

namespace V5Core
{
	class Input
	{

	public:
		friend class WindowsWindow;
		friend class AndroidWindow;
		friend class Core;
		static bool IsKeyDown(int key);
		static bool IsKeyHold(int key);

		static bool IsMouseButtonDown(int key);
		static bool IsMouseButtonHold(int key);
		static std::array<double, 2>& GetMousePosition();

	private:

		static void UpdateMousePos(double x, double y);
		static void MouseCallback(int key, int action);
		static void ResetDownKeys();

#ifdef V5_PLATFORM_WINDOWS
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif

		//Windows
		static bool s_keyDown[MAX_KEYS];
		static bool s_keyHold[MAX_KEYS];

		static bool s_mouseDown[MAX_KEYS];
		static bool s_mouseHold[MAX_KEYS];

		//Android


		//Common
		static std::array<double, 2> s_mousePosition;
	};
}

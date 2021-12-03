#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include <V5/Core/PlatformDetection.h>
#ifdef V5_PLATFORM_WINDOWS
#include <Windows.h>  //Windows before glad (otherwise API macro redefinition spamming warning)
#endif
#include <glad/glad.h> //Glad before glfw
#include "GLFW/glfw3.h"


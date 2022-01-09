#include "ImGuiLayer.h"
#include <V5/Core/PlatformDetection.h>
#ifdef V5_PLATFORM_WINDOWS
#ifdef V5_GRAPHCIS_API_OPENGL
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#endif
#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Core/IWindow.h>
#include <V5/Scene/Scene.h>
#endif

void ImGuiLayer::OnAttach(Scene* scene)
{	
#ifdef V5_PLATFORM_WINDOWS
#ifdef V5_GRAPHICS_API_OPENGL
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Factory::GetWindow().GetNative(), false);
	ImGui_ImplOpenGL3_Init("#version 460");
#endif
#endif
}

void ImGuiLayer::OnDetach()
{
#ifdef V5_PLATFORM_WINDOWS
#ifdef V5_GRAPHICS_API_OPENGL
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
#endif
}

void ImGuiLayer::Begin()
{
#ifdef V5_PLATFORM_WINDOWS
#ifdef V5_GRAPHICS_API_OPENGL

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif
#endif
}
void ImGuiLayer::End()
{
#ifdef V5_PLATFORM_WINDOWS
#ifdef V5_GRAPHICS_API_OPENGL
	ImGui::Render();
	auto data = ImGui::GetDrawData();
	ImGui_ImplOpenGL3_RenderDrawData(data);
#endif
#endif
}


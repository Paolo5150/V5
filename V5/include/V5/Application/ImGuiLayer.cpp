#include "ImGuiLayer.h"
#include <V5/Core/PlatformDetection.h>
#ifdef V5_PLATFORM_WINDOWS
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Core/IWindow.h>
#endif

void ImGuiLayer::OnAttach()
{	
#ifdef V5_PLATFORM_WINDOWS

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Factory::GetWindow().GetNative(), false);
	ImGui_ImplOpenGL3_Init("#version 410");
#endif
}

void ImGuiLayer::OnDetach()
{
#ifdef V5_PLATFORM_WINDOWS

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
}

void ImGuiLayer::Begin()
{
#ifdef V5_PLATFORM_WINDOWS

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif
}
void ImGuiLayer::End()
{
#ifdef V5_PLATFORM_WINDOWS

	ImGui::Render();
	auto data = ImGui::GetDrawData();
	ImGui_ImplOpenGL3_RenderDrawData(data);
#endif
}


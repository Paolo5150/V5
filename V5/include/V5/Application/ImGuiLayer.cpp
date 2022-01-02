#include "ImGuiLayer.h"
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Core/IWindow.h>

void ImGuiLayer::OnAttach()
{	
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Factory::GetWindow().GetNative(), false);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void ImGuiLayer::End()
{
	ImGui::Render();
	auto data = ImGui::GetDrawData();
	ImGui_ImplOpenGL3_RenderDrawData(data);
}


#include "EditorLayer.h"
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Renderer/IRenderer.h>
#include <V5/Core/IWindow.h>
#include <V5/Debugging/Intrumentor.h>
#include <V5/Components/Components.h>
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>

using namespace V5Rendering;
using namespace V5Core;



void EditorLayer::OnAttach(Scene* scene)
{
	V5_PROFILE_FUNCTION();

	m_editorCamera = std::make_unique<EditorCamera>(75, 
		(float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight(), 0.1f, 1000.0f);


	m_activeScene = scene;
}

void EditorLayer::OnUpdate(double dt) 
{
	static float timer = 0;
	static double timer2 = 0.0;
	timer += dt;
	timer2 += dt;

	m_editorCamera->OnUpdate(dt);


	switch (m_editorState)
	{
		case EditorState::EDIT:
			m_activeScene->UpdateEditor(dt);

			break;

		case EditorState::PLAY:
			m_activeScene->UpdateRuntime(dt);
			break;
	}

	if (timer > 0.5)
	{
		timer = 0;
		m_frameTime = 1.0f / (float)dt;
	}
}

void EditorLayer::OnRender()
{
	V5_PROFILE_FUNCTION();

	switch (m_editorState)
	{
	case EditorState::EDIT:
		m_activeScene->RenderEditor(*m_editorCamera);
		break;

	case EditorState::PLAY:
		break;
	}
}

void EditorLayer::OnImGuiRender()
{
	
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
		if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
		if (ImGui::MenuItem("Quit")) 
		{
			WindowCloseEvent wce;
			Factory::GetCore().TriggerEvent(wce);
		}
		ImGui::EndMenu();
	}

	ImGui::NextColumn();
	ImGui::Text("%f", m_frameTime);

	ImGui::EndMainMenuBar();
	
}



void EditorLayer::OnEvent(V5Core::Event& e) 
{
	if (e.GetType() == V5Core::EventType::MouseBtnClick)
	{
		//V5CLOG_INFO("EditorLayer received {0}", e.GetType());
	}
	else if (e.GetType() == V5Core::EventType::WindowClose)
	{
		//V5CLOG_INFO("closing");
	}
	else if (e.GetType() == V5Core::EventType::WindowResize)
	{
		//V5CLOG_INFO("closing");
		WindowResizeEvent& ev = dynamic_cast<WindowResizeEvent&>(e);
		m_editorCamera->UpdateProjectionMatrix(75, (float)ev.GetWidth() / ev.GetHeight(), 0.1f, 1000.0f);
	}
}
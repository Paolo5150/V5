#include "EditorLayer.h"
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/Factory.h>
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Core/IWindow.h>
#include <V5/Renderer/Texture.h>
#include <V5/Debugging/Intrumentor.h>
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include "V5/Scene/Scene.h"
#include "V5/Scene/Entity.h"


using namespace V5Rendering;
using namespace V5Core;

struct position
{
	float x;
	float y;
};

void EditorLayer::OnAttach()
{
	V5_PROFILE_FUNCTION();

	m_editorCamera = std::make_unique<EditorCamera>(75, 
		(float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight(), 0.6f, 1000.0f);


	Scene scene;
	auto ent = scene.CreateEntity();

	ent.AddComponent<position>(3.3f, 4.0f);

	V5CLOG_INFO("Has pos {0}", ent.HasComponent<position>());

}

void EditorLayer::OnUpdate(double dt) 
{
	m_frameTime = 1.0f / dt;
	m_editorCamera->OnUpdate(dt);

	static float timer = 0;
	timer += dt;
	if (timer > 0.5)
	{
		timer = 0;
		V5CLOG_INFO("FPS {0}", 1.0 / dt);
	}

}

void EditorLayer::OnRender()
{
	V5_PROFILE_FUNCTION();
	V5Core::Factory::GetRenderer2D().Begin(m_editorCamera->GetViewProjectionMatrix());

	for (int i = 0; i < 100000; i++)
	{
		V5Core::Factory::GetRenderer2D().DrawQuad({ i * 2,0,0.5 }, { 1,0,0 });

	}

	V5Core::Factory::GetRenderer2D().End();
}

void EditorLayer::OnImGuiRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("FPS");
	ImGui::Text("%f", m_frameTime);
	ImGui::End();	
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
}
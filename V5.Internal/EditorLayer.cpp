#include "EditorLayer.h"
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/Factory.h>
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Core/IWindow.h>
#include <V5/Renderer/Texture.h>
#include <V5/Debugging/Intrumentor.h>
#include <V5/Components/Components.h>
#include <V5/ImGui/imgui.h>
#include <V5/Utils/Random.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include "V5/Scene/Entity.h"


using namespace V5Rendering;
using namespace V5Core;
using namespace V5Utils;

namespace
{
	constexpr int QUAD_COUNT = 400000;
	std::unique_ptr<Texture2D> tt;
	std::vector<Entity> entities;
}

void EditorLayer::OnAttach()
{
	V5_PROFILE_FUNCTION();

	m_editorCamera = std::make_unique<EditorCamera>(75, 
		(float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight(), 0.1f, 1000.0f);

	tt = Texture2D::Create("Assets\\Textures\\smiley.png");

	for (int i = 0; i < QUAD_COUNT; i++)
	{
		auto e = m_activeScene.CreateEntity();
		e.GetComponent<Transform>().SetPosition({ i * 2, 0, 0});
		e.AddComponent<TileRenderer>(tt.get());
		entities.push_back(e);
	}

}

void EditorLayer::OnUpdate(double dt) 
{
	static float timer = 0;
	static float timer2 = 0;
	timer += dt;
	timer2 += dt;

	m_frameTime = 1.0f / (float)dt;
	m_editorCamera->OnUpdate(dt);



	switch (m_editorState)
	{
		case EditorState::EDIT:
			m_activeScene.UpdateEditor(dt);

			break;

		case EditorState::PLAY:
			m_activeScene.UpdateRuntime(dt);
			break;
	}




	if (timer > 0.5)
	{
		timer = 0;
		V5CLOG_INFO("FPS {0}", 1.0 / dt);
	}

}

void EditorLayer::OnRender()
{
	V5_PROFILE_FUNCTION();

	switch (m_editorState)
	{
	case EditorState::EDIT:
		m_activeScene.RenderEditor(*m_editorCamera);

		break;

	case EditorState::PLAY:
		break;
	}



}

void EditorLayer::OnImGuiRender()
{
	/*ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("FPS");
	ImGui::Text("%f", m_frameTime);
	ImGui::End();	*/
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
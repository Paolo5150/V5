#include "EditorLayer.h"
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Renderer/IRenderer.h>
#include <V5/Core/IWindow.h>
#include <V5/Renderer/Texture.h>
#include <V5/Debugging/Intrumentor.h>
#include <V5/Components/Components.h>
#include <V5/ImGui/imgui.h>
#include <V5/Utils/Random.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include <V5/Core/AssetManager.h>
#include "V5/Scene/Entity.h"


using namespace V5Rendering;
using namespace V5Core;
using namespace V5Utils;

namespace
{
	constexpr int QUAD_COUNT = 12;
	std::unique_ptr<Texture2D> tt;
	std::unique_ptr<Texture2D> tt2;
	std::vector<Entity> entities;
	Entity par;
}

void EditorLayer::OnAttach()
{
	V5_PROFILE_FUNCTION();

	m_editorCamera = std::make_unique<EditorCamera>(75, 
		(float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight(), 0.1f, 1000.0f);

	auto td = AssetManager::Instance().LoadTextureData("Textures\\smiley.png",true);
	auto td2 = AssetManager::Instance().LoadTextureData("Textures\\wall.jpg",true);
	tt = Texture2D::Create(td);
	tt2 = Texture2D::Create(td2);

	for (int i = 0; i < QUAD_COUNT; i++)
	{
		auto e = m_activeScene.CreateEntity();
		e.GetComponent<Transform>().SetPosition({ i * 2, 0, 0});
		e.GetComponent<Transform>().SetRotation({ 0,0,90});
		e.AddComponent<TileRenderer>(tt.get());

		e.GetComponent<Transform>().UpdateMatrix();
		entities.push_back(e);
	}

	// Try cube
	par = m_activeScene.CreateEntity();
	par.AddComponent<SpriteRenderer>(tt.get());

	auto e = m_activeScene.CreateEntity();
	e.GetComponent<Transform>().SetPosition({ 0,0,0.5 });
	e.AddComponent<SpriteRenderer>(tt2.get());
	e.GetComponent<Transform>().UpdateMatrix();
	e.GetComponent<Transform>().SetParent(par.GetComponent<Transform>());

	auto e2 = m_activeScene.CreateEntity();
	e2.GetComponent<Transform>().SetPosition({ 0,0.5,0 });
	e2.GetComponent<Transform>().SetRotation({ -90,0,0 });
	e2.AddComponent<SpriteRenderer>(tt2.get());
	e2.GetComponent<Transform>().UpdateMatrix();

	auto e3 = m_activeScene.CreateEntity();
	e3.GetComponent<Transform>().SetPosition({ 0,-0.5,0 });
	e3.GetComponent<Transform>().SetRotation({ 90,0,0 });
	e3.AddComponent<SpriteRenderer>(tt2.get());
	e3.GetComponent<Transform>().UpdateMatrix();

	auto e4 = m_activeScene.CreateEntity();
	e4.GetComponent<Transform>().SetPosition({ 0,0,-0.5 });
	e4.GetComponent<Transform>().SetRotation({ 0,180,0 });
	e4.AddComponent<SpriteRenderer>(tt2.get());
	e4.GetComponent<Transform>().UpdateMatrix();

	auto e5 = m_activeScene.CreateEntity();
	e5.GetComponent<Transform>().SetPosition({ 0.5,0,0 });
	e5.GetComponent<Transform>().SetRotation({ 0,90,0 });
	e5.AddComponent<SpriteRenderer>(tt2.get());
	e5.GetComponent<Transform>().UpdateMatrix();

	auto e6 = m_activeScene.CreateEntity();
	e6.GetComponent<Transform>().SetPosition({ -0.5,0,0 });
	e6.GetComponent<Transform>().SetRotation({ 0,-90,0 });
	e6.AddComponent<SpriteRenderer>(tt2.get());
	e6.GetComponent<Transform>().UpdateMatrix();

}

void EditorLayer::OnUpdate(double dt) 
{
	static float timer = 0;
	static double timer2 = 0.0;
	timer += dt;
	timer2 += dt;

	m_editorCamera->OnUpdate(dt);

	par.GetComponent<Transform>().SetPosition({ timer2 * 0.2f,0,0 });

	par.GetComponent<Transform>().UpdateMatrix();

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
		m_frameTime = 1.0f / (float)dt;
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
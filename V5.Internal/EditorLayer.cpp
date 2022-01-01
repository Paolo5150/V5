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
#include "V5/Scene/Scene.h"
#include "V5/Scene/Entity.h"


using namespace V5Rendering;
using namespace V5Core;
using namespace V5Utils;

namespace
{
	constexpr int QUAD_COUNT = 200000;
	Transform transforms[QUAD_COUNT];
	std::shared_ptr<Texture2D> tt;
}

struct position
{
	float x;
	float y;
};

void EditorLayer::OnAttach()
{
	V5_PROFILE_FUNCTION();

	m_editorCamera = std::make_unique<EditorCamera>(75, 
		(float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight(), 0.1f, 1000.0f);

	tt = Texture2D::Create("Assets\\Textures\\smiley.png");

	Scene scene;
	auto ent = scene.CreateEntity();

	ent.AddComponent<position>(3.3f, 4.0f);

	for (int i = 0; i < QUAD_COUNT; i++)
	{
		transforms[i].SetPosition({ i * 2, 0, 0.5 });

	}

}

void EditorLayer::OnUpdate(double dt) 
{
	m_frameTime = 1.0f / dt;
	m_editorCamera->OnUpdate(dt);

	static float timer = 0;
	static float timer2 = 0;
	timer += dt;
	timer2 += dt;


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


	for (int i = 0; i < QUAD_COUNT; i++)
	{
		V5Core::Factory::GetRenderer2D().DrawQuad(transforms[i], {1,1,1,1}, i % 2 == 0 ? tt : nullptr);

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
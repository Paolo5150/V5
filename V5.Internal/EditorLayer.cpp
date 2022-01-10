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
#include <V5/Core/Time.h>
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#include <sstream>
#include <optional>

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

void EditorLayer::ToggleState()
{
    if (m_editorState == EditorState::EDIT)
    {
        m_editorState = EditorState::PLAY;
        m_activeScene->OnStart();
    }
    else
    {
        m_editorState = EditorState::EDIT;
        m_activeScene->OnEnd();
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
		m_activeScene->RenderRuntime(m_editorCamera->GetViewProjectionMatrix());

		break;
	}
}

void EditorLayer::OnImGuiRender()
{
    //Currentl OpenGL only
#ifdef V5_PLATFORM_WINDOWS
#ifdef V5_GRAPHICS_API_OPENGL

    bool open = true;
    bool* p_open = &open;
    auto w = V5Core::Factory().GetWindow().GetWidth();
    auto h = V5Core::Factory().GetWindow().GetHeight();
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                WindowCloseEvent wce;
                V5Core::Factory().GetCore().TriggerEvent(wce);
            }
            ImGui::EndMenu();
        }

        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f));
        std::string btnText = m_editorState == EditorState::EDIT ? "Play" : "Stop";
        if (ImGui::Button(btnText.c_str()))
        {
            ToggleState();
        }

        ImGui::EndMenuBar();
        ImGui::Begin("Scene", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        
        int counter = 0;
        static std::optional<uint32_t> current;
        m_activeScene->ForEachEntity([&](uint32_t eID)
            {
                Entity eb(eID, m_activeScene);

                std::stringstream ss;
                ss << eb.GetComponent<Info>().Name << "(" << eb.GetComponent<Info>().Tag << ")" << counter;
                if (ImGui::Button(ss.str().c_str()))
                {
                    if (current.has_value())
                    {
                        Entity e(current.value(), m_activeScene);
                        if (e.HasComponent<SpriteRenderer>())
                        {
                            e.GetComponent<SpriteRenderer>().Color = { 1,1,1,1 };
                        }
                        if (e.HasComponent<TileRenderer>())
                        {
                            e.GetComponent<TileRenderer>().Color = { 1,1,1,1 };
                        }
                    }

                    Entity e(eID, m_activeScene);
                    if (e.HasComponent<SpriteRenderer>())
                    {
                        e.GetComponent<SpriteRenderer>().Color = { 1,0,0,1 };
                    }
                    if (e.HasComponent<TileRenderer>())
                    {
                        e.GetComponent<TileRenderer>().Color = { 1,0,0,1 };
                    }

                    current = e;
                }

                counter++;

            });

        ImGui::Text("Entities: %d", counter);
        ImGui::End();

        ImGui::Begin("Properties", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        if (current.has_value())
        {
            Entity e(current.value(), m_activeScene);
            ImGui::Text("%s (%s)", e.GetComponent<Info>().Name, e.GetComponent<Info>().Tag);
            ImGui::Separator();

            const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "Transform");
            if (open)
            {
                auto& tran = e.GetComponent<Transform>();
                ImGui::Text("Position:");
                ImGui::SameLine();
                float x = tran.GetPosition().x;
                if (ImGui::InputFloat("X", &x, 0.05f, 0.5f, "%.3f"))
                {
                    tran.SetPosition({ x, tran.GetPosition().y, tran.GetPosition().z });
                    tran.UpdateMatrix();
                }

                ImGui::TreePop();
            }

        }
        ImGui::End();
        ImGui::End();



    }
#endif
#endif
}



void EditorLayer::OnEvent(V5Core::Event& e) 
{
	if (e.GetType() == V5Core::EventType::MouseBtnClick)
	{
	}
	else if (e.GetType() == V5Core::EventType::WindowClose)
	{
	}
	else if (e.GetType() == V5Core::EventType::WindowResize)
	{
		WindowResizeEvent& ev = dynamic_cast<WindowResizeEvent&>(e);
		m_editorCamera->UpdateProjectionMatrix(75, (float)ev.GetWidth() / ev.GetHeight(), 0.1f, 1000.0f);
	}
}
#include <V5/Application/Application.h>
#include <V5/Core/Logger.h>
#include <V5/Event/Event.h>
#include <V5/Core/Layer.h>
#include <V5/Debugging/Intrumentor.h>
#ifdef V5_PLATFORM_WINDOWS
#include <V5/ImGui/imgui.h>
#include <V5/ImGui/imgui_impl_opengl3.h>
#include <V5/ImGui/imgui_impl_glfw.h>
#endif

using namespace V5Core;

Application::Application(std::string name) :
	m_name(name)
{
}

void Application::PushLayer(Layer* layer)
{
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{

	m_layerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Application::OnStart()
{
	V5LOG_INFO("App {0} start", m_name);
	m_imGuiLayer = new ImGuiLayer();
	PushOverlay(m_imGuiLayer);


}
void Application::Update(double dt)
{
	for (Layer* layer : m_layerStack)
		layer->OnUpdate(dt);
}

void Application::Render()
{
	for (Layer* layer : m_layerStack)
		layer->OnRender();

	m_imGuiLayer->Begin();
	for (Layer* layer : m_layerStack)
		layer->OnImGuiRender();
	m_imGuiLayer->End();
}



void Application::OnQuit()
{
	V5LOG_INFO("App {0} quit", m_name);
	V5_PROFILE_FUNCTION();
	m_layerStack.ClearLayers();

}

void Application::OnEvent(Event& e)
{
	V5LOG_INFO("App {0} event {1}", m_name, e.GetType());

	for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
	{
		if (e.GetIsConsumed())
			break;
		(*it)->OnEvent(e);
	}

}
		
		
		
		
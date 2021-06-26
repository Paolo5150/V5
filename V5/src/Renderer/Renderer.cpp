#include <Renderer/Renderer.h>

using namespace V5Rendering;

std::unique_ptr<Renderer> Renderer::s_Instance;

Renderer& Renderer::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Renderer>();
	}

	return *s_Instance;
}

void Renderer::Init()
{
	m_renderAPI = RendererAPI::Create();
	m_renderAPI->Init();
}

void Renderer::Shutdown()
{
	m_renderAPI->Shutdown();
}

void Renderer::OnEvent(V5Core::Event& e)
{
	m_renderAPI->OnEvent(e);
}



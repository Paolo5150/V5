#include "EditorLayer.h"
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>
#include <V5/Renderer/Texture.h>
#include <V5/Debugging/Intrumentor.h>

using namespace V5Rendering;

void EditorLayer::OnAttach()
{
	V5_PROFILE_FUNCTION();
	TextureData texture = V5Rendering::Texture::LoadData("Assets\\Textures\\wall.jpg");
	V5CLOG_INFO("Texture w {0} h {1}", texture.Width, texture.Height);
	texture.Delete();
}

void EditorLayer::OnUpdate() 
{
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
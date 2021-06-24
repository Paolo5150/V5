#include "EditorLayer.h"

void EditorLayer::OnUpdate() 
{

}

void EditorLayer::OnEvent(V5Core::Event& e) 
{
	if (e.GetType() == V5Core::EventType::MouseBtnClick)
	{
		V5CLOG_INFO("EditorLayer received {0}", e.GetType());
	}
	else if (e.GetType() == V5Core::EventType::WindowClose)
	{
		V5CLOG_INFO("closing");
		system("pause");
	}
}
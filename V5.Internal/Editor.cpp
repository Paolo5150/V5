#include "Editor.h"
#include "EditorLayer.h"
#include "GUILayer.h"
#include <V5/Debugging/Intrumentor.h>
#include <V5/Scene/TestScene.h>

void Editor::OnStart()
{
	Application::OnStart();

	m_activeScene = std::make_unique<TestScene>();
	V5_PROFILE_FUNCTION();
	PushLayer(new EditorLayer());
	PushOverlay(new GUILayer());
}

#include "Editor.h"
#include "EditorLayer.h"
#include "GUILayer.h"
#include <V5/Debugging/Intrumentor.h>

void Editor::OnStart()
{
	Application::OnStart();
	V5_PROFILE_FUNCTION();
	PushLayer(new EditorLayer());
	PushOverlay(new GUILayer());
}

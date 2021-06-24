#include <iostream>
#include <V5/Core/ICore.h>
#include <V5/Core/Factory.h>
#include "Editor.h"
#include <V5/Core/Logger.h>
#include "EditorLayer.h"
#include "GUILayer.h"
void main()
{
	Editor editor;
	editor.PushLayer(new EditorLayer());
	editor.PushLayer(new GUILayer());
	V5Core::Factory::Instance().GetCore().Start(&editor, 800, 600, "V5 Editor");
}
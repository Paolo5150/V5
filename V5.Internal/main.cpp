#include <iostream>
#include <V5/Core/ICore.h>
#include <V5/Core/Factory.h>
#include "Editor.h"
#include <V5/Core/Logger.h>

void main()
{
	Editor editor;
	V5Core::Factory::Instance().GetCore().Start(&editor, 800, 600, "V5 Editor");
}
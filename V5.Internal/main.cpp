#include <iostream>
#include <V5/Core/ICore.h>
#include <V5/Core/Factory.h>
#include "Editor.h"
#include <V5/Core/Logger.h>
#include <V5/Debugging/Intrumentor.h>

#include <future>
#include <chrono>

void main()
{
	Editor editor;
	V5Core::Factory::GetCore().Start(&editor, 1080, 540, "V5 Editor");




}
#pragma once

#include "../Dll.h"

namespace V5Core
{

	class V5_API Application
	{
	public:
		virtual void OnStart() = 0;
		virtual void Update() = 0;
		virtual void OnQuit() = 0;
	};
}

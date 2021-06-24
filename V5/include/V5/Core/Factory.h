#pragma once

#include "../Dll.h"

namespace V5Core
{
	class IWindow;
	class ICore;
	class ITime;

	class V5_API Factory
	{
	public:
		static Factory& Instance();

		IWindow& GetWindow();
		ICore& GetCore();
		ITime& GetTime();

	private:
		static std::unique_ptr<Factory> s_Instance;

	};
}

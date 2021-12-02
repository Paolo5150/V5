#pragma once

namespace V5Core
{
	class IWindow;
	class ICore;
	class ITime;

	class Factory
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

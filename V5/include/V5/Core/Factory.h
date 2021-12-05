#pragma once

namespace V5Rendering
{
	class IRenderer;
	class IRenderer2D;
}

namespace V5Core
{
	class IWindow;
	class ICore;


	class Factory
	{
	public:
		static Factory& Instance();

		IWindow& GetWindow();
		ICore& GetCore();
		V5Rendering::IRenderer& GetRenderer();
		V5Rendering::IRenderer2D& GetRenderer2D();

	private:
		static std::unique_ptr<Factory> s_Instance;

	};
}

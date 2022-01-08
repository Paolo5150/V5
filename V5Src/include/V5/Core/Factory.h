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

		static IWindow& GetWindow();
		static ICore& GetCore();
		static V5Rendering::IRenderer& GetRenderer();
		static V5Rendering::IRenderer2D& GetRenderer2D();

	};
}

#pragma once

namespace V5Rendering
{
	class IRenderer2D;

	class IRenderer
	{
	public:

		virtual IRenderer2D& GetRenderer2D() = 0;

		//Use for debug, render whatever
		virtual void DrawSample() = 0;

	};
}
#pragma once

namespace V5Rendering
{
	class IRenderer2D;
	
	struct RenderingStats
	{
		double FPSAveragePerSecond;

		uint32_t DrawCalls;
		uint32_t TotalVertices;
		double Time;

	};

	class IRenderer
	{
	public:

		virtual IRenderer2D& GetRenderer2D() = 0;
		virtual RenderingStats& GetRenderStats() = 0;
	};
}
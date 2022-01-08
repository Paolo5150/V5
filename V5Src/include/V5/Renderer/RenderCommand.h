
namespace V5Rendering
{
	class RenderCommand
	{
	public:
		static void SetClearColor(float r, float g, float b, float a);
		static void SetDepthTestEnabled(bool enabled);
		static void SetCullEnabled(bool enabled);
	};
}
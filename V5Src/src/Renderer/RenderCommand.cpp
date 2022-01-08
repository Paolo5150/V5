#include <V5/Renderer/RenderCommand.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/Renderer.h>

using namespace V5Rendering;

void RenderCommand::SetClearColor(float r, float g, float b, float a)
{
	Renderer::Instance().GetRenderAPI().SetClearColor(r, g, b, a);
}

void RenderCommand::SetDepthTestEnabled(bool enabled)
{

}
void RenderCommand::SetCullEnabled(bool enabled)
{

}

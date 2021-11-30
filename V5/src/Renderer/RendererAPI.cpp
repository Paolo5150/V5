#include <V5/Core/PlatformDetection.h>
#include "RendererAPI.h"

#ifdef  API_OPENGL
#include "OpenGL/OpenGLRendererAPI.h"
#endif
using namespace V5Rendering;

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
	/*switch (s_API)
	{
	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLRendererAPI>();
	default:
		break;
	}
	throw std::runtime_error("Graphics API unknown!");
	return nullptr;*/

#ifdef  API_OPENGL
	return std::make_unique<OpenGLRendererAPI>();

#endif //  API_OPENGL

}

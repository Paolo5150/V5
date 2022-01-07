#include <V5/Renderer/Texture.h>
#include <Renderer/RendererAPI.h>
#include <Core/CoreLogger.h>


#ifdef V5_PLATFORM_WINDOWS
#include <Renderer/OpenGL/OpenGLTexture2D.h>
#endif
#ifdef V5_PLATFORM_ANDROID
#include <Renderer/OpenGLES2/OpenGLES2Texture2D.h>

#endif

using namespace V5Rendering;

void TextureData::Delete()
{
	if (LoadingOK)
	{
		stbi_image_free(Data);
	}
	else
	{
		delete Data;
	}
}

std::unique_ptr<Texture2D> Texture2D::Create(const TextureDescription& desc)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLTexture2D>(desc);
#endif
#ifdef V5_PLATFORM_ANDROID

		case RendererAPI::API::OpenGLES:
			return std::make_unique<OpenGLES2Texture2D>(desc);
#endif
		default:
			break;
	}
	return nullptr;
}

std::unique_ptr<Texture2D> Texture2D::Create(TextureData& data,  const TextureDescription& desc)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLTexture2D>(data, desc);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES2Texture2D>(data, desc);
#endif
	default:
		break;
	}
	return nullptr;
}



std::unique_ptr<Texture2D> Texture2D::Create(TextureData& data,
											Texture2DWrapMode sWrap	,		
											Texture2DWrapMode tWrap	,		
											Texture2DFilter minFilter,		
											Texture2DFilter magFilter)		
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLTexture2D>(data, sWrap, tWrap, minFilter, magFilter);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES2Texture2D>(data, sWrap, tWrap, minFilter, magFilter);
#endif
	default:
		break;
	}
	return nullptr;
}


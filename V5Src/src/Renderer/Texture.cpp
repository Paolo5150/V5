#include <V5/Renderer/Texture.h>
#include <Renderer/RendererAPI.h>
#include <Core/CoreLogger.h>
#define STB_IMAGE_IMPLEMENTATION
#include <V5/Renderer/stb_image.h>

#ifdef V5_PLATFORM_WINDOWS
#include <Renderer/OpenGL/OpenGLTexture2D.h>
#endif
#ifdef V5_PLATFORM_ANDROID
#include <Renderer/OpenGLES2/OpenGLES2Texture2D.h>

#endif

using namespace V5Rendering;

void TextureData::Delete()
{
	if (m_loadingOK)
	{
		stbi_image_free(Data);
	}
	else
	{
		delete Data;
	}
}

TextureData Texture::CreateColorTextureData(float r, float g, float b)
{
	TextureData d;

	unsigned char* t = (unsigned char*)malloc(4);

	// Purple texture
	t[0] = (unsigned char)(r * 255);
	t[1] = (unsigned char)(g * 255);
	t[2] = (unsigned char)(b * 255);
	t[3] =  255;


	d.Data = t;
	d.Width = 1;
	d.Height = 1;
	d.Channels = 4;
	d.m_loadingOK = true;
	return d;
}



TextureData Texture::LoadData(const std::string& filePath, bool flipVertical)
{
	TextureData d;
	FILE* file = fopen(filePath.c_str(), "r");

	if (file == NULL)
	{
		V5CORE_LOG_CRITICAL("File {0} does not exist!", filePath);
		V5CLOG_CRITICAL("File {0} does not exist!", filePath);
		unsigned char* t =(unsigned char*)malloc(3);

		// Purple texture
		t[0] = 255;
		t[1] = 0;
		t[2] = 255;
		d.Data = t;
		d.Width = 1;
		d.Height = 1;
		d.Channels = 3;
		d.m_loadingOK = false;
	}
	else
	{
		int w, h, c;
		stbi_set_flip_vertically_on_load(flipVertical);
		auto data = stbi_load(filePath.c_str(), &w, &h, &c, 0);
		if (data)
		{
			d.Data = data;
			d.Width = w;
			d.Height = h;
			d.Channels = c;
			d.m_loadingOK = true;

		}
		else
		{
			V5CORE_LOG_CRITICAL("Texture {0} failed to load!", filePath);
			V5CLOG_CRITICAL("Texture {0} failed to load!", filePath);
			unsigned char* t = new unsigned char;
			// Purple texture

			t[0] = 255;
			t[1] = 0;
			t[2] = 255;
			d.Data = t;
			d.Width = 1;
			d.Height = 1;
			d.Channels = 3;
			d.m_loadingOK = false;

		}
	}


	return d;
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

std::unique_ptr<Texture2D> Texture2D::Create(float r, float g, float b)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLTexture2D>(r,g,b);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES2Texture2D>(r,g,b);
#endif
	default:
		break;
	}
	return nullptr;
}



std::unique_ptr<Texture2D> Texture2D::Create(std::string filePath,
											Texture2DWrapMode sWrap	,		
											Texture2DWrapMode tWrap	,		
											Texture2DFilter minFilter,		
											Texture2DFilter magFilter)		
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLTexture2D>(filePath, sWrap, tWrap, minFilter, magFilter);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES2Texture2D>(filePath, sWrap, tWrap, minFilter, magFilter);
#endif
	default:
		break;
	}
	return nullptr;
}


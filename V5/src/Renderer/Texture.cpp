#include <V5/Renderer/Texture.h>
#include <filesystem>
#include <Renderer/RendererAPI.h>
#include <Core/CoreLogger.h>
#define STB_IMAGE_IMPLEMENTATION
#include <V5/Renderer/stb_image.h>
#include <Renderer/OpenGL/OpenGLTexture2D.h>

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

TextureData Texture::LoadData(const std::string& filePath)
{
	TextureData d;

	if (!std::filesystem::exists(filePath))
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

std::shared_ptr<Texture2D> Texture2D::Create(std::string filePath)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLTexture2D>(filePath);
	default:
		break;
	}
	return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(uint32_t w, uint32_t h, Texture2DSizeFormat format)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLTexture2D>(w,h,format);
	default:
		break;
	}
	return nullptr;
}
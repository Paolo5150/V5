#include <V5/Renderer/Texture.h>
#include <filesystem>
#include <Core/CoreLogger.h>
#define STB_IMAGE_IMPLEMENTATION
#include <V5/Renderer/stb_image.h>

using namespace V5Rendering;

void TextureData::Delete()
{
	stbi_image_free(Data);
}

TextureData Texture::LoadData(const std::string& filePath)
{
	TextureData d;

	if (!std::filesystem::exists(filePath))
	{
		V5CORE_LOG_CRITICAL("File {0} does not exist!", filePath);
		V5CLOG_CRITICAL("File {0} does not exist!", filePath);

		//TODO: throw excp> load default text?
	}
	else
	{
		int w, h, c;

		auto data = stbi_load(filePath.c_str(), &w, &h, &c, 4);
		if (data)
		{
			d.Data = data;
			d.Width = w;
			d.Height = h;
			d.Channels = c;
		}
		else
		{
			V5CORE_LOG_CRITICAL("Texture {0} failed to load!", filePath);
			V5CLOG_CRITICAL("Texture {0} failed to load!", filePath);
		}
	}

	return d;
}

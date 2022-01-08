#include <V5/Core/AssetManager.h>
#include <fstream>
#include <V5/Core/Logger.h>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <V5/Renderer/stb_image.h>

using namespace V5Core;

std::unique_ptr<AssetManager> AssetManager::s_Instance;

AssetManager& AssetManager::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<AssetManager>();
	}

	return *s_Instance;
}

void AssetManager::Initialize(std::string assetFolderPath)
{
	m_assetFolderPath = assetFolderPath;
}


std::string AssetManager::ReadTextFile(const char* path)
{
	std::ifstream inStream(m_assetFolderPath + std::string("/") + path);
	
	if (inStream.is_open())
	{
		std::istreambuf_iterator<char> startIt(inStream), endIt;
		std::vector<char> buffer(startIt, endIt);
		inStream.close();

		std::string s(buffer.begin(), buffer.end());

		return s;
	}
	
	V5LOG_ERROR("Cannot open {0}", path);
	return {};
	

}


std::vector<char> AssetManager::ReadAssetBinary(const char* path)
{
	std::ifstream inStream(m_assetFolderPath + std::string("/") + path, std::ios::binary);
	if (inStream.is_open())
	{
		std::istreambuf_iterator<char> startIt(inStream), endIt;
		std::vector<char> buffer(startIt, endIt);
		inStream.close();
		return buffer;
	}
	else
	{
		V5LOG_ERROR("Cannot open {0}", path);
		return {};
	}
	
}

TextureData AssetManager::CreateColorTextureData(float r, float g, float b)
{
	TextureData d;

	unsigned char* t = (unsigned char*)malloc(4);

	// Purple texture
	t[0] = (unsigned char)(r * 255);
	t[1] = (unsigned char)(g * 255);
	t[2] = (unsigned char)(b * 255);
	t[3] = 255;

	d.Data = t;
	d.Width = 1;
	d.Height = 1;
	d.Channels = 4;
	d.LoadingOK = true;
	return d;
}

TextureData AssetManager::LoadTextureData(const std::string& filePath, bool flipVertical)
{
	std::stringstream ss;
	ss << m_assetFolderPath << "/" << filePath;
	TextureData d;
	FILE* file = fopen(ss.str().c_str(), "r");

	if (file == NULL)
	{
		V5CLOG_ERROR("File {0} does not exist!", filePath);
		unsigned char* t = (unsigned char*)malloc(3);

		// Purple texture
		t[0] = 255;
		t[1] = 0;
		t[2] = 255;
		d.Data = t;
		d.Width = 1;
		d.Height = 1;
		d.Channels = 3;
		d.LoadingOK = false;
	}
	else
	{
		fclose(file);
		int w, h, c;
		stbi_set_flip_vertically_on_load(flipVertical);
		auto data = stbi_load(ss.str().c_str(), &w, &h, &c, 0);
		if (data)
		{
			d.Data = data;
			d.Width = w;
			d.Height = h;
			d.Channels = c;
			d.LoadingOK = true;

		}
		else
		{
			V5CLOG_ERROR("Texture {0} failed to load: {1}", filePath, stbi_failure_reason());
			unsigned char* t = new unsigned char;
			// Purple texture

			t[0] = 255;
			t[1] = 0;
			t[2] = 255;
			d.Data = t;
			d.Width = 1;
			d.Height = 1;
			d.Channels = 3;
			d.LoadingOK = false;

		}
	}


	return d;
}

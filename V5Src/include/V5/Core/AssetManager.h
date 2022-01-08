#pragma once
#include <iostream>
#include <vector>
#include <V5/Renderer/Texture.h>

namespace V5Core
{
	class AssetManager
	{
	public:
		static AssetManager& Instance();

		void Initialize(std::string assetFolderPath); // For now, only called by Android main.cpp
		std::vector<char> ReadAssetBinary(const char* path);
		std::string ReadTextFile(const char* path);
		TextureData LoadTextureData(const std::string& filePath, bool flipVertical);
		TextureData CreateColorTextureData(float r, float g, float b);

	private:
		static std::unique_ptr<AssetManager> s_Instance;
		std::string m_assetFolderPath = "Assets"; //Default. Android will override this
	};
}

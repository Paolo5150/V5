#include <V5/Core/AssetManager.h>
#include <fstream>
#include <V5/Core/Logger.h>
#include <sstream>

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
	//std::stringstream ss;
	//ss << m_assetFolderPath << "/" << path;


	//FILE* f = fopen(ss.str().c_str(), "r");
	//if (f != nullptr)
	//{
	//	V5LOG_INFO("FILE FOUND!!!");

	//}
	//else
	//{
	//	V5LOG_ERROR("FILE not fonud............");
	//}
	std::ifstream inStream(m_assetFolderPath + std::string("/") + path);
	
	std::istreambuf_iterator<char> startIt(inStream), endIt;
	std::vector<char> buffer(startIt, endIt);
	inStream.close();

	std::string s(buffer.begin(), buffer.end());

	return s;

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


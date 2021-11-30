#pragma once
#include <iostream>
#include <vector>
#include <V5/Renderer/stb_image.h>

namespace V5Rendering
{
	enum Texture2DSizeFormat
	{
		SRGB8,
		RGBA8,
		RGB8,
		RGBA16F,

	};


	struct TextureData
	{
		friend class Texture;
		void* Data;
		int Width;
		int Height;
		int Channels;

		void Delete();
	private:
		bool m_loadingOK;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void Bind(uint32_t slot) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		//TODO: thils will probably move into a potential Asset manager class
		static TextureData LoadData(const std::string& filePath);



	};

	class Texture2D : public Texture
	{
	public:

		 static std::shared_ptr<Texture2D> Create(uint32_t w, uint32_t h, Texture2DSizeFormat format = Texture2DSizeFormat::RGBA8);
		 static std::shared_ptr<Texture2D> Create(std::string filePath);
	};
}
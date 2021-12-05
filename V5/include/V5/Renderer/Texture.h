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
		RGBA16F
	};

	enum Texture2DFilter
	{
		LINEAR,
		NEAREST,
		LINEAR_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		NEAREST_MIPMAP_NEAREST
	};

	enum Texture2DWrapMode
	{
		CLAMP_TO_BORDER,
		CLEAMP_TO_EDGE,
		REPEAT
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
		 static std::shared_ptr<Texture2D> Create(std::string filePath);
	};
}
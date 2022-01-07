#pragma once
#include <iostream>
#include <vector>
#include <V5/Renderer/stb_image.h>

struct TextureData
{
	void* Data;
	int Width;
	int Height;
	int Channels;
	bool LoadingOK;

	void Delete();
};


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

	struct TextureDescription
	{
		uint32_t Width;
		uint32_t Height;
		Texture2DSizeFormat Format;
		Texture2DFilter MinFilter;
		Texture2DFilter MagFilter;
		Texture2DWrapMode SWrapMode;
		Texture2DWrapMode TWrapMpde;
	};


	

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void Bind(uint32_t slot) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

	};

	class Texture2D : public Texture
	{
	public:
		 static std::unique_ptr<Texture2D> Create(	TextureData&,
													Texture2DWrapMode sWrap = Texture2DWrapMode::REPEAT,
													Texture2DWrapMode tWrap = Texture2DWrapMode::REPEAT,
													Texture2DFilter minFilter = Texture2DFilter::LINEAR,
													Texture2DFilter magFilter = Texture2DFilter::LINEAR);

		 static std::unique_ptr<Texture2D> Create(const TextureDescription& desc);
		 static std::unique_ptr<Texture2D> Create(TextureData&, const TextureDescription& desc);
	};
}
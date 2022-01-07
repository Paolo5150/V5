#pragma once
#include <V5/Renderer/Texture.h>

namespace V5Rendering
{
	class OpenGLES2Texture2D : public Texture2D
	{
	public:
		OpenGLES2Texture2D(TextureData& data,
			Texture2DWrapMode sWrap,
			Texture2DWrapMode tWrap,
			Texture2DFilter minFilter,
			Texture2DFilter magFilter);

		OpenGLES2Texture2D(const TextureDescription& desc);
		OpenGLES2Texture2D(TextureData& data, const TextureDescription& desc);


		~OpenGLES2Texture2D();
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		void Bind(uint32_t slot) const override;
		void SetData(void* data, uint32_t size) override;

	private:
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_textureID;
		Texture2DSizeFormat m_sizeFormat;
	};
}
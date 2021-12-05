#pragma once
#include <V5/Renderer/Texture.h>

namespace V5Rendering
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(std::string filePath,
			Texture2DWrapMode sWrap,
			Texture2DWrapMode tWrap,
			Texture2DFilter minFilter,
			Texture2DFilter magFilter);

		OpenGLTexture2D(const TextureDescription& desc);

		~OpenGLTexture2D();
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
#include "OpenGLTexture2D.h"
#include <glad/gl.h>
#include <V5/Debugging/Intrumentor.h>


using namespace V5Rendering;
namespace
{

static GLenum Texture2DSizeFormatToOpenGLFormat(Texture2DSizeFormat type)
{
	switch (type)
	{
	case Texture2DSizeFormat::RGBA16F:   return GL_RGBA16F;
	case Texture2DSizeFormat::RGBA8:   return GL_RGBA8;
	case Texture2DSizeFormat::RGB8:   return GL_RGB8;
	case Texture2DSizeFormat::SRGB8:   return GL_SRGB8;

	}

	throw std::runtime_error("Unknown texture format");
	return 0;
}

static GLenum Texture2DSizeFormatToOpenGLInternalFormat(Texture2DSizeFormat type)
{
	switch (type)
	{
	case Texture2DSizeFormat::RGBA16F:   return GL_RGBA;
	case Texture2DSizeFormat::RGBA8:   return GL_RGBA;
	case Texture2DSizeFormat::SRGB8:   return GL_RGB;
	case Texture2DSizeFormat::RGB8:   return GL_RGB;
	}
	throw std::runtime_error("Unknown texture format");

	return 0;
}

static GLenum Texture2DSizeFormatToOpenGLType(Texture2DSizeFormat type)
{
	switch (type)
	{
	case Texture2DSizeFormat::RGBA16F:   return GL_FLOAT;
	case Texture2DSizeFormat::RGBA8:   return GL_UNSIGNED_BYTE;
	case Texture2DSizeFormat::RGB8:   return GL_UNSIGNED_BYTE;
	case Texture2DSizeFormat::SRGB8:   return GL_UNSIGNED_BYTE;
	}
	throw std::runtime_error("Unknown texture format");

	return 0;
}

static GLenum Texture2DFilterToOpenGLType(Texture2DFilter type)
{
	switch (type)
	{
		case Texture2DFilter::LINEAR:   return GL_LINEAR;
		case Texture2DFilter::NEAREST:   return GL_NEAREST;
		case Texture2DFilter::LINEAR_MIPMAP_LINEAR:   return GL_LINEAR_MIPMAP_LINEAR;
		case Texture2DFilter::LINEAR_MIPMAP_NEAREST:   return GL_LINEAR_MIPMAP_NEAREST;
		case Texture2DFilter::NEAREST_MIPMAP_LINEAR:   return GL_NEAREST_MIPMAP_LINEAR;
		case Texture2DFilter::NEAREST_MIPMAP_NEAREST:   return GL_NEAREST_MIPMAP_NEAREST;
	}
	throw std::runtime_error("Unknown texture filter");

	return 0;
}

static GLenum Texture2DWrapModeToOpenGLType(Texture2DWrapMode type)
{
	switch (type)
	{
		case Texture2DWrapMode::CLAMP_TO_BORDER:  return GL_CLAMP_TO_BORDER;
		case Texture2DWrapMode::CLEAMP_TO_EDGE:  return GL_CLAMP_TO_EDGE;
		case Texture2DWrapMode::REPEAT:  return GL_REPEAT;
	}
	throw std::runtime_error("Unknown texture wrap mode");

	return 0;
}
}


OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_textureID);
}

OpenGLTexture2D::OpenGLTexture2D(TextureData& data, const TextureDescription& desc)
{
	GLenum internalFormat = 0, dataFormat = 0;
	m_sizeFormat = Texture2DSizeFormat::RGBA8;

	internalFormat = Texture2DSizeFormatToOpenGLFormat(desc.Format);
	dataFormat = Texture2DSizeFormatToOpenGLInternalFormat(desc.Format);

	m_width = data.Width;
	m_height = data.Height;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
	glTextureStorage2D(m_textureID, 1, internalFormat, m_width, m_height);

	auto minF = Texture2DFilterToOpenGLType(Texture2DFilter::LINEAR);
	auto maxF = Texture2DFilterToOpenGLType(Texture2DFilter::LINEAR);

	auto wrapS = Texture2DWrapModeToOpenGLType(Texture2DWrapMode::REPEAT);
	auto wrapT = Texture2DWrapModeToOpenGLType(Texture2DWrapMode::REPEAT);

	glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, minF);
	glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, maxF);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, wrapS);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, wrapT);

	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);

	glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, dataType, data.Data);
	data.Delete();
}


OpenGLTexture2D::OpenGLTexture2D(const TextureDescription& desc) :
	m_sizeFormat(desc.Format)
{
	m_width = desc.Width;
	m_height = desc.Height;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
	glTextureStorage2D(m_textureID, 1, Texture2DSizeFormatToOpenGLFormat(desc.Format), m_width, m_height);

	auto minF = Texture2DFilterToOpenGLType(desc.MinFilter);
	auto maxF = Texture2DFilterToOpenGLType(desc.MagFilter);

	auto wrapS = Texture2DWrapModeToOpenGLType(desc.SWrapMode);
	auto wrapT = Texture2DWrapModeToOpenGLType(desc.TWrapMpde);

	glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, minF);
	glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, maxF);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, wrapS);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, wrapT);
}


OpenGLTexture2D::OpenGLTexture2D(TextureData& data,
								Texture2DWrapMode sWrap,
								Texture2DWrapMode tWrap,
								Texture2DFilter minFilter,
								Texture2DFilter magFilter) : 
	m_sizeFormat(Texture2DSizeFormat::RGBA8)

{
	GLenum internalFormat = 0, dataFormat = 0;
	if (data.Channels == 4)
	{
		m_sizeFormat = Texture2DSizeFormat::RGBA8;

		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (data.Channels == 3)
	{
		m_sizeFormat = Texture2DSizeFormat::RGB8;

		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	m_width = data.Width;
	m_height = data.Height;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
	glTextureStorage2D(m_textureID, 1, internalFormat, m_width, m_height);

	auto minF = Texture2DFilterToOpenGLType(minFilter);
	auto maxF = Texture2DFilterToOpenGLType(minFilter);

	auto wrapS = Texture2DWrapModeToOpenGLType(sWrap);
	auto wrapT = Texture2DWrapModeToOpenGLType(tWrap);

	glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, minF);
	glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, maxF);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, wrapS);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, wrapT);

	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);

	glTextureSubImage2D(m_textureID,0, 0, 0, m_width, m_height, dataFormat, dataType, data.Data);
	data.Delete();
}

uint32_t OpenGLTexture2D::GetWidth() const
{
	return m_width;
}

uint32_t OpenGLTexture2D::GetHeight() const
{
	return m_height;
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_textureID);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	auto dataFormat = Texture2DSizeFormatToOpenGLInternalFormat(m_sizeFormat);
	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);
	glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, dataType, data);
}
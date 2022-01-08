#include "OpenGLES2Texture2D.h"
#include <glad/gles2.h>
#include <V5/Debugging/Intrumentor.h>
#define V5_PLATFORM_ANDROID
#include <V5/Core/Logger.h>


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

OpenGLES2Texture2D::~OpenGLES2Texture2D()
{
	glDeleteTextures(1, &m_textureID);
}

OpenGLES2Texture2D::OpenGLES2Texture2D(TextureData& data, const TextureDescription& desc)
{
	GLenum internalFormat = 0, dataFormat = 0;
	m_sizeFormat = Texture2DSizeFormat::RGBA8;

	internalFormat = GL_RGBA8;
	dataFormat = GL_RGBA;

	m_width = data.Width;
	m_height = data.Height;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	auto minF = Texture2DFilterToOpenGLType(Texture2DFilter::LINEAR);
	auto maxF = Texture2DFilterToOpenGLType(Texture2DFilter::LINEAR);

	auto wrapS = Texture2DWrapModeToOpenGLType(Texture2DWrapMode::REPEAT);
	auto wrapT = Texture2DWrapModeToOpenGLType(Texture2DWrapMode::REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, dataType, data.Data);

	data.Delete();
}


OpenGLES2Texture2D::OpenGLES2Texture2D(const TextureDescription& desc) :
	m_sizeFormat(desc.Format)
{
	m_width = desc.Width;
	m_height = desc.Height;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	auto minF = Texture2DFilterToOpenGLType(desc.MinFilter);
	auto maxF = Texture2DFilterToOpenGLType(desc.MagFilter);

	auto wrapS = Texture2DWrapModeToOpenGLType(desc.SWrapMode);
	auto wrapT = Texture2DWrapModeToOpenGLType(desc.TWrapMpde);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	auto dataFormat = Texture2DSizeFormatToOpenGLInternalFormat(m_sizeFormat);
	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);
	auto sizeFormat = Texture2DSizeFormatToOpenGLFormat(m_sizeFormat);

	glTexImage2D(GL_TEXTURE_2D, 0, sizeFormat, m_width, m_height, 0, dataFormat, dataType, nullptr);


}


OpenGLES2Texture2D::OpenGLES2Texture2D(TextureData& data,
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

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	auto minF = Texture2DFilterToOpenGLType(minFilter);
	auto maxF = Texture2DFilterToOpenGLType(minFilter);

	auto wrapS = Texture2DWrapModeToOpenGLType(sWrap);
	auto wrapT = Texture2DWrapModeToOpenGLType(tWrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);
	auto format =   Texture2DSizeFormatToOpenGLInternalFormat(m_sizeFormat);
	auto sizeFormat =   Texture2DSizeFormatToOpenGLFormat(m_sizeFormat);

	glTexImage2D(GL_TEXTURE_2D, 0, sizeFormat, m_width, m_height, 0, dataFormat, dataType, data.Data);

	data.Delete();
}

uint32_t OpenGLES2Texture2D::GetWidth() const
{
	return m_width;
}

uint32_t OpenGLES2Texture2D::GetHeight() const
{
	return m_height;
}

void OpenGLES2Texture2D::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

}

void OpenGLES2Texture2D::SetData(void* data, uint32_t size)
{
	V5LOG_ERROR("NOT IMPLEMENTED!!!!!");
}
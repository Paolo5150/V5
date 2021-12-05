#include "OpenGLTexture2D.h"
#include <glad/glad.h>
#include <V5/Debugging/Intrumentor.h>


using namespace V5Rendering;

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


OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_textureID);
}

OpenGLTexture2D::OpenGLTexture2D(std::string filePath)
{
	TextureData texture = V5Rendering::Texture::LoadData(filePath);

	GLenum internalFormat = 0, dataFormat = 0;
	if (texture.Channels == 4)
	{
		m_sizeFormat = Texture2DSizeFormat::RGBA8;

		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (texture.Channels == 3)
	{
		m_sizeFormat = Texture2DSizeFormat::RGB8;

		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	m_width = texture.Width;
	m_height = texture.Height;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
	glTextureStorage2D(m_textureID, 1, internalFormat, m_width, m_height);

	glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);


	glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, dataType, texture.Data);
	texture.Delete();
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
	V5_PROFILE_FUNCTION();
	glBindTextureUnit(slot, m_textureID);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	auto dataFormat = Texture2DSizeFormatToOpenGLInternalFormat(m_sizeFormat);
	auto dataType = Texture2DSizeFormatToOpenGLType(m_sizeFormat);
	glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, dataType, data);
}
#include "Buffer.h"
#include "RendererAPI.h"
#include <V5/Core/PlatformDetection.h>

#ifdef V5_PLATFORM_WINDOWS
#include "OpenGL/OpenGLBuffer.h"
#endif

#ifdef V5_PLATFORM_ANDROID
#include "OpenGLES2/OpenGLES2Buffer.h"
#endif
using namespace V5Rendering;

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLVertexBuffer>(size);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_shared<OpenGLES2VertexBuffer>(size);
#endif
	default:
		break;
	}

	return nullptr;
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLVertexBuffer>(data, size);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_shared<OpenGLES2VertexBuffer>(data,size);
#endif
	default:
		break;
	}

	return nullptr;
}


std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLIndexBuffer>(indices, count);
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_shared<OpenGLES2IndexBuffer>(indices, count);
#endif
	default:
		break;
	}

	return nullptr;
}

std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t binding, const void* data, uint32_t size)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLUniformBuffer>(binding, data, size);
#endif
#ifdef V5_PLATFORM_ANDROID
	case RendererAPI::API::OpenGLES:
		return std::make_shared<OpenGLES2UniformBuffer>(binding, data, size);

#endif
	default:
		break;
	}

	return nullptr;
}

std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t binding, uint32_t size)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLUniformBuffer>(binding, size);
#endif
#ifdef V5_PLATFORM_ANDROID
	case RendererAPI::API::OpenGLES:
		return std::make_shared<OpenGLES2UniformBuffer>(binding, size);
#endif

	default:
		break;
	}

	return nullptr;
}


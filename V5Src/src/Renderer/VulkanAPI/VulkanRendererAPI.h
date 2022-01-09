#pragma once
#include "Renderer/RendererAPI.h"
#include <V5/Core/PlatformDetection.h>

#ifdef V5_PLAFTORM_ANDROID
#define VK_USE_PLATFORM_ANDROID_KHR 1
#endif
#include <../Vulkan/Include/vulkan/vulkan.h>

namespace V5Rendering
{
	class VulkanRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Shutdown() override;
		void OnEvent(V5Core::Event& e) override;

		void SetClearColor(float r, float g, float b, float a) const override;
		void SetViewport(int x, int y, int width, int height) const override;
		void RenderIndexed(VertexArray& aroverride) override;
		void RenderIndexed(VertexArray& aroverride, uint32_t indexCount) override;
		void RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount) override;
		void SetDepthTestEnabled(bool enabled) override;
		void SetCullEnabled(bool enabled) override;

		void Clear() override;

	private:
		VkInstance m_vulkanInstance;


	};
}
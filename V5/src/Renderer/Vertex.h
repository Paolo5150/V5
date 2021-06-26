#pragma once
#include <glm/glm.hpp>
#include "Renderer/Buffer.h"

namespace V5Rendering
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Color;

		static BufferLayout GetLayout()
		{
			BufferLayout l({
		BufferElement(ShaderDataType::Float3,"Position"),
		BufferElement(ShaderDataType::Float3,"Color")
				});

			return l;
		}

	};
}

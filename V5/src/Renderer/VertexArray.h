#pragma once
#include <iostream>

namespace V5Rendering
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray
	{
		public:
			virtual ~VertexArray() = default;
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vb) = 0;
			virtual void SetIndexBuffer(IndexBuffer& vb) = 0;

			static std::unique_ptr<VertexArray> Create();

		private:


	};
}
#pragma once
#include <vector>


namespace V5Rendering
{
	// Thanks Cherno
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		return 0;
	}



	class BufferElement
	{
	public:
		ShaderDataType DataType;
		uint32_t Size;
		bool Normalized;
		size_t Offset;
		bool Instanced;

		BufferElement(ShaderDataType type, bool normalized = false, bool instanced = false)
			: DataType(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized), Instanced(instanced)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (DataType)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3; // 3* float3
			case ShaderDataType::Mat4:    return 4; // 4* float4
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(std::vector<BufferElement> elements) : m_bufferElements(elements) {
			CalculateOffsetAndStride();
		};

		const std::vector<BufferElement>& GetBufferElements() const { return m_bufferElements; }
		uint32_t GetStride() const { return m_stride; }

	private:
		std::vector<BufferElement> m_bufferElements;

		void CalculateOffsetAndStride()
		{
			size_t offset = 0;
			for (auto& element : m_bufferElements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}

		uint32_t m_stride = 0; // Not initializing this costed me 1 full day of debugging

	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() = 0;
		virtual uint32_t GetID() const = 0;

		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(const void* data, uint32_t size);
	};

	class IndexBuffer
	{
	public:

		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetCount() const = 0;
		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);

	};

	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Bind(uint32_t shaderID) const = 0;

		virtual void Unbind() const = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual uint32_t GetID() const = 0;

		static std::shared_ptr<UniformBuffer> Create(uint32_t binding, uint32_t size);
		static std::shared_ptr<UniformBuffer> Create(uint32_t binding, const void* data, uint32_t size);
		static std::shared_ptr<UniformBuffer> Create(std::string uniformName, uint32_t size);
		static std::shared_ptr<UniformBuffer> Create(std::string uniformName, const void* data, uint32_t size);
	};
}
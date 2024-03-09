#pragma once
#include<initializer_list>

namespace Hazel {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			// 都是四个字节的
		case ShaderDataType::None:	 return 0;
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
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType dataType;
		uint32_t size;			// 数据类型大小
		uint32_t offset;
		bool isNormalize;

		BufferElement(){}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), dataType(type), size(ShaderDataTypeSize(type)), offset(0), isNormalize(normalized)
		{
		}
		// this is get numbers of DataType in shader  比如vec3就是 3个
		uint32_t GetComponentCount() const
		{
			switch (dataType)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_element(elements)
		{
			CalculateOffsetsAndStride();
		}
		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_element; }

		std::vector<BufferElement>::iterator begin() { return m_element.begin(); }
		std::vector<BufferElement>::iterator end() { return m_element.end(); }
		std::vector<BufferElement>::const_iterator begin() const{ return m_element.begin(); }
		std::vector<BufferElement>::const_iterator end() const{ return m_element.end(); }


	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (BufferElement& val : m_element) {
				val.offset = offset;

				offset += val.size;
				m_Stride = offset;
			}
		}

	private:
		std::vector<BufferElement> m_element;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);
		virtual void Bind() const = 0;
		virtual void UnBind()const = 0;


		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
	private:
	};

	class IndexBuffer {
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() = 0;

	private:
	};
}



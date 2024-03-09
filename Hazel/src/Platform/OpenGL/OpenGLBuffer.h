#pragma once
#include"Hazel/Renderer/Buffer.h"

namespace Hazel {

	class OpenGLVertexBuffer:public VertexBuffer{
	public:
		OpenGLVertexBuffer(float* vertex, uint32_t size);
		virtual void Bind() const;
		virtual void UnBind()const;
		virtual const BufferLayout& GetLayout() const override;
		virtual void SetLayout(const BufferLayout& layout) override;

	private:
		uint32_t m_RenderID;
		
		BufferLayout m_bufferLayout;
	};

	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual void Bind() const;
		virtual void UnBind() const;
		virtual uint32_t GetCount() override;
	private:
		uint32_t m_RenderID;
		uint32_t indicesCount;
	};
}


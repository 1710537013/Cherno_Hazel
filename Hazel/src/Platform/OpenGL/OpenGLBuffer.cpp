#include "hzpch.h"
#include "OpenGLBuffer.h"
#include"glad/glad.h"


namespace Hazel {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_RenderID);
		glBindVertexArray(m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}
	void OpenGLVertexBuffer::Bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}
	 void OpenGLVertexBuffer::UnBind()const
	 {
		 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 }

	 const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	 {
		 return m_bufferLayout;
	 }

	 void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	 {
		 m_bufferLayout = layout;
	 }




	 OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	 {
		 glGenBuffers(1, &m_RenderID);
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);

		 glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		 indicesCount = count;
	 }

	 void OpenGLIndexBuffer::Bind()const {
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	 }
	 void OpenGLIndexBuffer::UnBind()const
	 {
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	 }
	 uint32_t OpenGLIndexBuffer::GetCount()
	 {
		 return indicesCount;
	 }
}
#include "hzpch.h"
#include "OpenGLRenderAPI.h"
#include <glad/glad.h>


namespace Hazel {

	void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_DEPTH_BUFFER_BIT |GL_COLOR_BUFFER_BIT);
	}
	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r,color.g,color.b,color.a);
	}
}


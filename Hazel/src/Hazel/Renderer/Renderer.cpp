#include "hzpch.h"
#include "Renderer.h"
#include"RenderCommand.h"

namespace Hazel {
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		//RendererAPI::DrawIndexed(vertexArray)
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}
}
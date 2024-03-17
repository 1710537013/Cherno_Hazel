#include "hzpch.h"
#include"RenderCommand.h"
#include"Renderer.h"

namespace Hazel {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographyCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjMatrix();
	}
	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{

		shader->Bind();
		shader->UploadUniformMat4("viewProjection", m_SceneData->ViewProjectionMatrix);
		//RendererAPI::DrawIndexed(vertexArray)
		RenderCommand::DrawIndexed(vertexArray);
	}
}
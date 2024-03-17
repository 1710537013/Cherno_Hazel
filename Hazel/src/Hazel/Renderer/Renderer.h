#pragma once
#include "VertexArray.h"
#include"RendererAPI.h"
#include"OrthographyCamera.h"
#include "Shader.h"

namespace Hazel {

	// 渲染器只有一个所以说 为了方便做个静态类即可
	class Renderer
	{
	public:
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>&);
		static void BeginScene(OrthographyCamera& camera);
		static void EndScene();

		static RendererAPI::API GetRendererAPI() { return RendererAPI::GetRenderAPI(); }  // 已经有这个API了，感觉这里不用再写了

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
	private:

		static SceneData* m_SceneData;
	};
}

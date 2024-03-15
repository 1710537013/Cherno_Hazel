#pragma once
#include"RendererAPI.h"

namespace Hazel {
	class RenderCommand
	{
	public:
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			m_RendererAPI->DrawIndexed(vertexArray);
		}
		
		static void Clear() {
			m_RendererAPI->Clear();
		}
		static void SetClearColor(const glm::vec4& color ) {
			m_RendererAPI->SetClearColor(color);
		}

	private:
		static std::shared_ptr<RendererAPI> m_RendererAPI;
	};

}


#pragma once
#include"Hazel/Renderer/RendererAPI.h"

namespace Hazel {

	class OpenGLRenderAPI: public RendererAPI
	{
	public:
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&);


		// 通过 RendererAPI 继承
		virtual void Clear() override;

		virtual void SetClearColor(const glm::vec4& color) override;

	};


}


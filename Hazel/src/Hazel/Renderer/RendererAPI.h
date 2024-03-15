#pragma once
#include "VertexArray.h"

namespace Hazel {


	class RendererAPI
	{
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};

		static API GetRenderAPI() { return m_API; }

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

	private:

		static API m_API;
	};
}



#pragma once

namespace Hazel {
	enum class RendererAPI {
		None = 0,
		OpenGL = 1
	};


	class Renderer
	{
	public:
		static RendererAPI GetRenderAPI() { return m_RendererAPI; }
	private:
		static RendererAPI m_RendererAPI;
	};
}

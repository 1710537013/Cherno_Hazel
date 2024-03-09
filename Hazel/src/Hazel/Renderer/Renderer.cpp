#include "hzpch.h"
#include "Renderer.h"


namespace Hazel {
	RendererAPI Renderer::m_RendererAPI = RendererAPI::OpenGL;
	// 这里应该有个函数用户可以通过SetAPI来设置平台
}
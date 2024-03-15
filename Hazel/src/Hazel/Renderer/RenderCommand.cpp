#include "hzpch.h"
#include "RenderCommand.h"
#include"Platform/OpenGL/OpenGLRenderAPI.h"


namespace Hazel {
	std::shared_ptr<RendererAPI> RenderCommand::m_RendererAPI = std::make_shared<OpenGLRenderAPI>(OpenGLRenderAPI());  //  Mark 可能出错
	//RendererAPI* RenderCommand::m_RendererAPI = new OpenGLRenderAPI();  //  也可以这样
}
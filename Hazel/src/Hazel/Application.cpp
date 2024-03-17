#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <glad/glad.h>

#include "Input.h"
#include <Platform/OpenGL/OpenGLBuffer.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };
		
		m_vertexArray.reset(VertexArray::Create());
		//m_vertexArray = std::make_shared<OpenGLVertexArray>(VertexArray::Create());   为什么这样不行
		//m_vertexArray = std::make_shared<VertexArray>(VertexArray::Create());   //为什么这样不行

		m_vertexBuffer.reset( VertexBuffer::Create(vertices, sizeof(vertices)));
		std::shared_ptr<IndexBuffer> m_indexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		/*m_vertexBuffer->Bind();
		m_indexBuffer->Bind();*/

		BufferLayout bufferLayout(
			{ {ShaderDataType::Float3, "position"}, { ShaderDataType::Float4, "color" } }
		);
		m_vertexBuffer->SetLayout(bufferLayout);

		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_color;
			out vec3 v_Position;
			out vec4 v_color;
			
			uniform mat4 viewProjection;
			void main()
			{
				v_Position = a_Position;
				v_color = a_color;
				gl_Position = viewProjection*vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_color;
			void main()
			{
				color = v_color;//* 0.5 + 0.5
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		m_SquareVA.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<VertexBuffer> square_vertexBuffer(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		//std::shared_ptr<IndexBuffer> square_indexBuffer(IndexBuffer::Create(squareIndices ,std::size1(squareIndices)));
		std::shared_ptr<IndexBuffer> square_indexBuffer(IndexBuffer::Create(squareIndices ,sizeof(squareIndices)/sizeof(uint32_t)));
		BufferLayout square_layout{
			{ {ShaderDataType::Float3, "position"}}
		};
		square_vertexBuffer->SetLayout(square_layout);

		m_SquareVA->AddVertexBuffer(square_vertexBuffer);
		m_SquareVA->SetIndexBuffer(square_indexBuffer);
		//square_vertexBuffer->SetLayout()
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 viewProjection;
			void main()
			{
				v_Position = a_Position;
				gl_Position = viewProjection*vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
			RenderCommand::Clear();


			//m_Camera.SetPos({ 1.0f, 0.0f, 0.0f });
			m_Camera.SetRotation(45.0f);
			// begin

			Renderer::BeginScene(m_Camera);
			//draw one
			m_BlueShader->Bind();
			Renderer::Submit(m_BlueShader,m_SquareVA);
			// draw two
			m_Shader->Bind();
			Renderer::Submit(m_Shader,m_vertexArray);

			//end
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
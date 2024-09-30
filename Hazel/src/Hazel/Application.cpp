#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"


#include "Input.h"

#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel {

#define BIND_EVNET_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;



	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVNET_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		m_VertexArray.reset(VertexArray::Create());

		//, 1.0f, 0.0f, 1.0f, 1.0f
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		const std::string src1 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;


			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
                v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position,1.0);
			}
		)";

		const std::string src2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
            in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(new Shader(src1, src2));

		// DRAW SQUARE-------------------------------------
		m_VertexArraySQ.reset(VertexArray::Create());
		float verticesSQ[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> vertexBufferSQ;
		vertexBufferSQ.reset(VertexBuffer::Create(verticesSQ, sizeof(verticesSQ)));
		vertexBufferSQ->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_VertexArraySQ->AddVertexBuffer(vertexBufferSQ);


		uint32_t indicesSQ[6] = { 0, 1, 2,2,3,0 };
		std::shared_ptr<IndexBuffer> indexBufferSQ;
		indexBufferSQ.reset(IndexBuffer::Create(indicesSQ, sizeof(indicesSQ) / sizeof(uint32_t)));
		m_VertexArraySQ->SetIndexBuffer(indexBufferSQ);

		const std::string src12 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
           


			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
                v_Position = a_Position;
             
				gl_Position = vec4(a_Position,1.0);
			}
		)";

		const std::string src22 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
            in vec4 v_Color;

			void main()
			{
				color = vec4(0.2,0.3,0.8, 1.0);
				
			}
		)";

		m_ShaderSQ.reset(new Shader(src12, src22));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer) {
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVNET_FN(OnWindowClose));
		//HZ_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled) {
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{


			RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_ShaderSQ->Bind();
			Renderer::Submit(m_VertexArraySQ);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();



			for (Layer* layer : m_layerStack)
				layer->OnUpdate();
			

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}


}

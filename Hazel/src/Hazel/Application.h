#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Hazel/LayerStack.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"

#include "Hazel/Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Hazel/Renderer/OrthographicCamera.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_layerStack;

		/*unsigned int m_VertexArray;*/

		std::shared_ptr<Shader> m_Shader;
		//std::shared_ptr<VertexBuffer> m_VertexBuffer;
		//std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_ShaderSQ;
		/*std::shared_ptr<VertexBuffer> m_VertexBufferSQ;
		std::shared_ptr<IndexBuffer> m_IndexBufferSQ;*/
		std::shared_ptr<VertexArray> m_VertexArraySQ;
		
		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// TO be defined for Client
	Application* CreateApplication();
}



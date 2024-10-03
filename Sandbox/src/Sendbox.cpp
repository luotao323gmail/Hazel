#include <hzpch.h>
#include <Hazel.h>


#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
//glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
//{
//	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
//	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//	return Projection * View * Model;
//}


class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
		, m_CameraPosition(0.0f)
		, m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		//, 1.0f, 0.0f, 1.0f, 1.0f
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		const std::string src1 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;


            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
                v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
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
		m_Shader.reset(new Hazel::Shader(src1, src2));

		// DRAW SQUARE-------------------------------------
		m_VertexArraySQ.reset(Hazel::VertexArray::Create());
		float verticesSQ[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Hazel::VertexBuffer> vertexBufferSQ;
		vertexBufferSQ.reset(Hazel::VertexBuffer::Create(verticesSQ, sizeof(verticesSQ)));
		vertexBufferSQ->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position" }
			});
		m_VertexArraySQ->AddVertexBuffer(vertexBufferSQ);


		uint32_t indicesSQ[6] = { 0, 1, 2,2,3,0 };
		std::shared_ptr<Hazel::IndexBuffer> indexBufferSQ;
		indexBufferSQ.reset(Hazel::IndexBuffer::Create(indicesSQ, sizeof(indicesSQ) / sizeof(uint32_t)));
		m_VertexArraySQ->SetIndexBuffer(indexBufferSQ);

		const std::string src12 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
           
			uniform mat4 u_ViewProjection;

            uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
                v_Position = a_Position;
             
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		const std::string src22 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
           

			void main()
			{
				color = vec4(0.2,0.3,0.8, 1.0);
				
			}
		)";

		m_ShaderSQ.reset(new Hazel::Shader(src12, src22));
	}

	void OnImGuiRender() override
	{

	}

	void OnUpdate(Hazel::Timestep ts) override
	{

		HZ_CLIENT_TRACE("Delta time:{0}s,{1}ms", ts.GetSeconds(), ts.GetMillseconds());
		
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_K))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}

		Hazel::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		Hazel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		for (int y = -5; y < 5; y++) {
			for (int x = -5; x < 5; x++) {

				glm::vec3 pos(x * 0.11f, y*0.11f, 0.0f);

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazel::Renderer::Submit(m_VertexArraySQ, m_ShaderSQ, transform);
			}
		}
	

		//Hazel::Renderer::Submit(m_VertexArray, m_Shader);

		Hazel::Renderer::EndScene();

	}

	void OnEvent(Hazel::Event& event) override
	{
	}



private:


	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;

	std::shared_ptr<Hazel::Shader> m_ShaderSQ;
	std::shared_ptr<Hazel::VertexArray> m_VertexArraySQ;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;

	float m_SquareMoveSpeed = 1.0f;

	glm::vec3 m_SquarePosition;

};


class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}

	~Sandbox()
	{

	}
};


Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}

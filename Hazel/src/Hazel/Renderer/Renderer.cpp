#include "hzpch.h"
#include "Renderer.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProejcrtMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(
		
		 const Ref<Shader>& shader
		, const Ref<VertexArray>& vertexArray
		, const glm::mat4& transfomr
	)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProejcrtMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transfomr);

		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}
}
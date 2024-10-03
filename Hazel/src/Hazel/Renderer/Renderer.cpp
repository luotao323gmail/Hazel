#include "hzpch.h"
#include "Renderer.h"
#include "OrthographicCamera.h"
#include "Shader.h"

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
		const std::shared_ptr<VertexArray>& vertexArray
		, const std::shared_ptr<Shader>& shader
		, const glm::mat4& transfomr
	)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProejcrtMatrix);
		shader->UploadUniformMat4("u_Transform", transfomr);

		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}
}
// Source file for Renderer
#include "Xpch.h"
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
#include "XEngine/Renderer/RendererAPI/Renderer2D.h"
namespace XEngine
{
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{ 
		XPROFILE_FUNCTION();
		RenderCommand::Init(); 
		Renderer2D::Init();
	}
	void Renderer::Shutdown()
		{ Renderer2D::Shutdown(); }
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
		{ RenderCommand::SetViewport(0, 0, width, height); }
	void Renderer::BeginScene(OrthographicCamera& camera)
		{ m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix(); }
	void Renderer::EndScene() {}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}

// byjohnmichael

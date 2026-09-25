// Header file for Renderer
#pragma once
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/CameraSystem/Cameras.h"
#include "XEngine/Renderer/RendererAPI/RendererAPI.h"
#include "XEngine/Renderer/RendererAPI/RenderCommand.h"
namespace XEngine
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();
		static RendererAPI::API GetAPI()
			{ return RendererAPI::GetAPI(); }
	private:
		// Struct
		struct SceneData
			{ glm::mat4 ViewProjectionMatrix; };
		// Member
		static Scope<SceneData> m_SceneData;
	};
}

// byjohnmichael

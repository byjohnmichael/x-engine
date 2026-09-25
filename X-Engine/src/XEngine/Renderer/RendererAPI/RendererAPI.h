// Header file to choose the Renderering API
#pragma once
#include <glm/glm.hpp>
#include "XEngine/Renderer/VertexArray.h"
namespace XEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
		virtual ~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		static Scope<RendererAPI> Create();
		static API GetAPI()
			{ return m_RenderAPI; }
	private:
		static API m_RenderAPI;
	};
}

// byjohnmichael

// Render Command Header file
#pragma once
#include "XEngine/Renderer/RendererAPI/RendererAPI.h"
namespace XEngine
{
	class RenderCommand
	{
	public:
		static void Init()
			{ m_CommandAPI->Init(); }
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
			{ m_CommandAPI->SetViewport(x, y, width, height); }
		static void SetClearColor(const glm::vec4& color)
			{ m_CommandAPI->SetClearColor(color); }
		static void Clear()
			{ m_CommandAPI->Clear(); }
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
			{ m_CommandAPI->DrawIndexed(vertexArray, count); }
	private:
		static Scope<RendererAPI> m_CommandAPI;
	};
}

// byjohnmichael

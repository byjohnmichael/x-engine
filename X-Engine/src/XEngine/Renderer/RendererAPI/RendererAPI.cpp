// Source file to choose the Renderering API
#include "Xpch.h"
#include "XEngine/Renderer/RendererAPI/RendererAPI.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLRendererAPI.h"
namespace XEngine
{
	RendererAPI::API RendererAPI::m_RenderAPI = RendererAPI::API::OpenGL;
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (m_RenderAPI)
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

// byjohnmichael

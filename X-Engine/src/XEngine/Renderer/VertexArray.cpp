// Source file for vertex array class 
#include "Xpch.h"
#include "XEngine/Renderer/VertexArray.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLVertexArray.h"
namespace XEngine
{
	Ref<VertexArray> VertexArray::Create()
	{
		XPROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: 
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

// byjohnmichael

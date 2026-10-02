// Source file for base framebuffer class
#include "Xpch.h"
#include "XEngine/Renderer/Framebuffer.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLFramebuffer.h"
namespace XEngine
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecificaion& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
		}
		XCORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}

// byjohnmichael

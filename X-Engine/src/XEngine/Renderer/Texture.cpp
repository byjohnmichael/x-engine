// Source file for texture and texture2D class 
#include "Xpch.h"
#include "XEngine/Renderer/Texture.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLTexture.h"
namespace XEngine
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XCORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

// byjohnmichael

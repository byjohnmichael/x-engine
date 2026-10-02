// Source file for base shader class, also contains functions for shader library
#include "Xpch.h"
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
namespace XEngine
{
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(path);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexShader, fragmentShader);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	// Shader Library Functions
	void ShaderLibrary::Add(Ref<Shader>& shader, const std::string& name)
	{
		XCORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	void ShaderLibrary::Add(Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(shader, name);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& path, const std::string& name)
	{
		auto shader = Shader::Create(path);
		Add(shader, name);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		XCORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
		{ return m_Shaders.find(name) != m_Shaders.end(); }
}

// byjohnmichael

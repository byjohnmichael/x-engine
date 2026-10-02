// Header file for OpenGL Shader, derives from shader class
#pragma once
#include <glm/glm.hpp>
#include "XEngine/Renderer/Shader.h"
typedef uint32_t GLenum;
namespace XEngine
{
	class OpenGLShader : public Shader
	{
	public:
		// Defined in Source File
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
		virtual ~OpenGLShader();
		void Bind() const override;
		void Unbind() const override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		virtual const std::string& GetName() const override
			{ return m_Name; }
	private:
		// Functions
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		// Members
		std::string m_Name;
		uint32_t m_RendererID;
	};
}

// byjohnmichael

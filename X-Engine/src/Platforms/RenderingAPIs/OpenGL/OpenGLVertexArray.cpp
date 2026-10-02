// Source file for OpenGL Vertex Arrays
#include "Xpch.h"
#include <GLAD/glad.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLVertexArray.h"
namespace XEngine
{
	static GLenum ShaderTypeConvertToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3: return GL_FLOAT;
			case ShaderDataType::Mat4: return GL_FLOAT;
			case ShaderDataType::Int: return GL_INT;
			case ShaderDataType::Int2: return GL_INT;
			case ShaderDataType::Int3: return GL_INT;
			case ShaderDataType::Int4: return GL_INT;
			case ShaderDataType::Bool: return GL_BOOL;
		}
		XCORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		XPROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		XPROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		XPROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		XPROFILE_FUNCTION();
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		XCORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			uint8_t count = 0;
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index, element.GetComponentCount(), ShaderTypeConvertToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
					index++;
					break;
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
					count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(index);
						glVertexAttribPointer(index, count, ShaderTypeConvertToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(index, 1);
						index++;
					}
					break;
				default:
					XCORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}
		m_VertexBuffer.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}

// byjohnmichael

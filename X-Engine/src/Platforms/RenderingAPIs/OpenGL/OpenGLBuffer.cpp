// Source File for Vertex and Index Buffer Functions
#include "Xpch.h"
#include <GLAD/glad.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLBuffer.h"
namespace XEngine
{
	// Vertex Buffer Functions
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		XPROFILE_FUNCTION();
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		XPROFILE_FUNCTION();
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		XPROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RenderID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	// Index Buffer Functions
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		XPROFILE_FUNCTION();
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		XPROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RenderID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

// byjohnmichael

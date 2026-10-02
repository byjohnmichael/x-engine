// Source file for Framebuffer Class
#include "Xpch.h"
#include <GLAD/glad.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLFramebuffer.h"
namespace XEngine
{
	static const uint32_t maxFramebufferSize = 8192;
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecificaion& spec) : m_Spec(spec)
		{ Invalidate(); }
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
	}
	void OpenGLFramebuffer::Unbind()
		{ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > maxFramebufferSize || height > maxFramebufferSize)
		{
			XCORE_WARN("Attempted to resize frame buffer to {0}, {1}", width, height);
			return;
		}
		m_Spec.Width = width;
		m_Spec.Height = height;
		Invalidate();
	}
	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
		XCORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

// byjohnmichael

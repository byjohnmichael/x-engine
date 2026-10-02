// Header file for OpenGL Framebuffer, derives from Framebuffer
#pragma once
#include "XEngine/Renderer/Framebuffer.h"
namespace XEngine
{
	class OpenGLFramebuffer : public Framebuffer 
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecificaion& spec);
		virtual ~OpenGLFramebuffer();
		virtual void Bind();
		virtual void Unbind();
		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual uint32_t GetColorAttachmentRendererID() const override
			{ return m_ColorAttachment; }
		void Invalidate();
		virtual const FramebufferSpecificaion& GetSpecificaion() const override
			{ return m_Spec; }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecificaion m_Spec;
	};
}

// byjohnmichael

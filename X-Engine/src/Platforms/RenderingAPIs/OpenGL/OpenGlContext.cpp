// Source file for OpenGL Context Class
#include "Xpch.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGlContext.h"
namespace XEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* mainwindowHandle) : m_WindowHandle(mainwindowHandle)
	{
		XCORE_ASSERT(mainwindowHandle, "Window handle doesn't exist or is equal to null!");
		XCORE_INFO("OpenGL Context has been created");
	}
	void OpenGLContext::Init()
	{
		XPROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XCORE_ASSERT(status, "Failed to initialize Glad!");
		XCORE_INFO("Glad has been initialized!");
		XCORE_INFO("OpenGL Renderer: {0} {1} {2} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
		XCORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "X-Engine requires at least OpenGL version 4.5!");
	}
	void OpenGLContext::SwapBuffers()
	{
		XPROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}

// byjohnmichael

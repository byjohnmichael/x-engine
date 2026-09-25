// Source file for Win10Window class functions, configured for Windows 10, also derived from window class
#include "Xpch.h"
#include <wtypes.h>
#include "XEngine/Core/Input.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGlContext.h"
#include "Platforms/OperatingSystems/Windows10/Win10Window.h"
namespace XEngine
{
	static uint8_t GLFWWindowCount = 0;
	static void GLFWErrorCallback(int error, const char* description)
		{ XCORE_ERROR("GLFW Error ({0}): {1}", error, description); };
	Win10Window::Win10Window(const WindowProps& props)
	{
		XPROFILE_FUNCTION();
		XCORE_INFO("Using Windows 10 Window Class");
		Init(props);
	}
	Win10Window::~Win10Window()
	{
		XPROFILE_FUNCTION();
		Shutdown();
	}
	void Win10Window::Init(const WindowProps& props)
	{
		XPROFILE_FUNCTION();
		SetConsoleTitle(TEXT("X-Engine Console"));
		m_WindowData.Title = props.Title;
		m_WindowData.Width = props.Width;
		m_WindowData.Height = props.Height;
		if (GLFWWindowCount == 0)
		{
			int success = glfwInit();
			XCORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			XCORE_INFO("GLFW intialized");
		}
		{
			XPROFILE_SCOPE("glfwCreateWindow");
			#if defined(XDEBUG)
				if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
					glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif
				m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
			++GLFWWindowCount;
		}
		m_WindowContext = GraphicsContext::Create(m_Window);
		m_WindowContext->Init();
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVSync(false);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}
	void Win10Window::Shutdown()
	{
		XPROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
		--GLFWWindowCount;
		if (GLFWWindowCount == 0)
		{
			XCORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}
	void Win10Window::OnUpdate()
	{
		XPROFILE_FUNCTION();
		glfwPollEvents();
		m_WindowContext->SwapBuffers();
	}
	void Win10Window::SetVSync(bool enabled)
	{
		XPROFILE_FUNCTION();
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_WindowData.VSync = enabled;
	}
	bool Win10Window::IsVSync() const
		{ return m_WindowData.VSync; }
}

// byjohnmichael

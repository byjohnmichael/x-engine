// Application Source file is used to start up the window, push layers, and other things
#include "Xpch.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "XEngine/Core/Input.h"
#include "XEngine/Core/KeyCodes.h"
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Core/Application.h"
#include "XEngine/Renderer/RendererAPI/Renderer.h"
namespace XEngine
{
	Application* Application::m_Instance = nullptr;
	Application::Application(const std::string& applicationName)
	{
		XPROFILE_FUNCTION();
		XCORE_INFO("Application starting");
		XCORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;
		m_Window = Window::Create(WindowProps(applicationName));
		m_Window->SetEventCallback(XBIND_EVENT_FN(Application::OnEvent));
		Renderer::Init();
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	Application::~Application()
	{
		XPROFILE_FUNCTION();
		XCORE_INFO("Application Shutting Down");
		Renderer::Shutdown();
	}
	void Application::PushLayer(Layer* layer)
	{
		XPROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		XPROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::Close()
		{ m_Running = false; }
	void Application::OnEvent(Event& e)
	{
		XPROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(XBIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(XBIND_EVENT_FN(Application::OnWindowResize));
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.m_Handled)
				break;
			(*it)->OnEvent(e);
		}
	}
	// Core of application where everything gets updated
	void Application::Run() 
	{
		XPROFILE_FUNCTION();
		while (m_Running)
		{
			XPROFILE_SCOPE("Run Loop");
			// Timestep calculation
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			// Update Layers
			if (!m_Minimized)
			{
				{
					// Updates all of the OnUpdate functions
					XPROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
				// ImGui Update
				m_ImGuiLayer->Begin();
				{
					XPROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}
			// Update Window
			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		XPROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}

// byjohnmichael

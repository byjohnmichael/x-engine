// Header file for the Application Class
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/Core/XCore.h"
#include "XEngine/Core/Window.h"
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/Buffer.h"
#include "XEngine/ImGui/ImGuiLayer.h"
#include "XEngine/EventSystem/Event.h"
#include "XEngine/Renderer/VertexArray.h"
#include "XEngine/LayerSystem/LayerStack.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/Renderer/CameraSystem/Cameras.h"
int main(int argc, char** argv);
namespace XEngine
{
	class Application
	{
	public:
		Application(const std::string& applicationName = "X-Engine");
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		Window& GetWindow()
			{ return *m_Window; }
		static Application& Get()
			{ return *m_Instance; }
		ImGuiLayer* GetImGuiLayer()
			{ return m_ImGuiLayer; }
		void Close();
	private:
		// Functions
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		friend int ::main(int argc, char** argv);
		// Members
		bool m_Running = true;
		bool m_Minimized = false;
		static Application* m_Instance;
		std::unique_ptr<XEngine::Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime = 0.0f;
	};
	Application* CreateApplication();
}

// byjohnmichael

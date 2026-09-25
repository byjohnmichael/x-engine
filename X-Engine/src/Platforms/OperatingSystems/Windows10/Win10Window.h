// Header file for Win10Window class, configured for Windows 10
#pragma once
#include <GLFW/glfw3.h>
#include "XEngine/Core/Window.h"
#include "XEngine/Renderer/GraphicsContext.h"
namespace XEngine
{
	class Win10Window : public Window
	{
	public:
		Win10Window(const WindowProps& props);
		virtual ~Win10Window();
		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		uint32_t GetWidth() const override
			{ return m_WindowData.Width; }
		uint32_t GetHeight() const override
			{ return m_WindowData.Height; }
		void SetEventCallback(const EventCallbackFn& callback) override 
			{ m_WindowData.EventCallback = callback; }
		virtual void* GetNativeWindow() const 
			{ return m_Window; }
	private:
		// Functions
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		// Structs
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		// Members
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_WindowContext;
		WindowData m_WindowData;
	};
}

// byjohnmichael

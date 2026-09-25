// Window class and window properties struct
#pragma once
#include <sstream>
#include "XEngine/Core/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	struct WindowProps
	{
		// Functions
		WindowProps(const std::string& title = "X-Engine", uint32_t width = 1600, uint32_t height = 900) : Title(title), Width(width), Height(height) {}
		// Members
		std::string Title;
		uint32_t Width;
		uint32_t Height;
	};
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}

// byjohnmichael

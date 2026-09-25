// Source file for Window class, decides to create a window based on the platform
#include "Xpch.h"
#include "XEngine/Core/Window.h"
#ifdef XPLATFORM_WINDOWS
	#include "Platforms/OperatingSystems/Windows10/Win10Window.h"
#endif
namespace XEngine
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef XPLATFORM_WINDOWS
			return CreateScope<Win10Window>(props);
		#else
			XCORE_ASSERT(false, "Unknown Platform");
			return nullptr;
		#endif
	}
}

// byjohnmichael

// Where the game source code is written, stored, and called
#include <XEngine.h>
#include "Layers/EditorLayer.h"
#include "XEngine/Core/EntryPoint.h"
namespace XEngine
{
	class XEditor : public Application
	{
	public:
		XEditor() : Application("X-Editor")
		{ 
			XCORE_INFO("X-Editor starting");
			PushLayer(new EditorLayer());
		}
		~XEditor() { XCORE_INFO("X-Editor shutting down"); }
	};
	Application* CreateApplication() { return new XEditor(); }
}

// byjohnmichael

// Game takes data from the X-Editor and builds it into standalone game here
#include "XEngine.h"
#include "XEngine/Core/EntryPoint.h"
class Game : public XEngine::Application
{
public:
	Game() { XCORE_INFO("Game starting"); }
	~Game() { XCORE_INFO("Game shutting down"); }
};
XEngine::Application* XEngine::CreateApplication() { return new Game(); }
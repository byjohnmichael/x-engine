// Entry Point of X-Engine
#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/Debug/Instrumentor.h"
#ifdef XPLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	printf("-----Starting X-Engine-----\n");
	XEngine::Logging::Init();
	XPROFILE_BEGIN_SESSION("Startup", "XEngineProfile-Startup.json");
	auto app = XEngine::CreateApplication();
	XPROFILE_END_SESSION();
	XPROFILE_BEGIN_SESSION("Runtime", "XEngineProfile-Runtime.json");
	app->Run();
	XPROFILE_END_SESSION();
	XPROFILE_BEGIN_SESSION("Shutdown", "XEngineProfile-Shutdown.json");
	delete app;
	XPROFILE_END_SESSION();
	printf("-----X-Engine Shutdown-----");
}
#endif

// byjohnmichael

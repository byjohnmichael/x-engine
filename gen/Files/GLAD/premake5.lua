project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	files
	{
		"include/GLAD/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
	}
	includedirs 
		{ "include" }
	filter "system:windows"
		systemversion "latest"
	filter "configurations:Debug"
		symbols "on"
		runtime "Debug"
	filter "configurations:Release"
		optimize "on"
		runtime "Release"

-- byjohnmichael

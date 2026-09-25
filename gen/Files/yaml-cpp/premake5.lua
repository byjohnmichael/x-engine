outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	files
	{
		"src/**.h",
		"src/**.cpp",
		"include/**.h"
	}
	includedirs
		{ "include" }
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"
	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		staticruntime "Off"
	filter "configurations:Release"
		runtime "Release"
		optimize "on"

-- byjohnmichael

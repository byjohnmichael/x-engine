@echo off
PUSHD ..\..\
COPY gen\Files\GLFW\premake5.lua X-Engine\vendor\GLFW\
COPY gen\Files\ImGui\premake5.lua X-Engine\vendor\ImGui
COPY gen\Files\GLAD\premake5.lua X-Engine\vendor\GLAD
COPY gen\Files\yaml-cpp\premake5.lua X-Engine\vendor\yaml-cpp
COPY gen\Files\X-Engine\premake5.lua
CALL vendor\Premake\premake5.exe vs2019
DEL premake5.lua
DEL X-Engine\vendor\GLAD\premake5.lua
DEL X-Engine\vendor\ImGui\premake5.lua
DEL X-Engine\vendor\GLFW\premake5.lua
DEL X-Engine\vendor\yaml-cpp\premake5.lua
POPD
PAUSE
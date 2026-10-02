#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/Scene/Scene.h"
namespace XEngine
{

	class Details
	{
	public:
		Details() = default;
		void OnImGuiRender(Entity& m_SelectionContext);
	};
}

// byjohnmichael

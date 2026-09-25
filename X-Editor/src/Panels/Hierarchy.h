#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/Scene/Scene.h"
#include "XEngine/Scene/Entity.h"
namespace XEngine
{
	class Hierarchy
	{
	public:
		// Methods
		Hierarchy() = default;
		Hierarchy(const Ref<Scene>& context);
		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();
		// Members
		Entity m_SelectionContext;
	private:
		// Methods
		void DrawEntityNode(Entity entity);
		// Members
		Ref<Scene> m_Context;
	};
}

// byjohnmichael

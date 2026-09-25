#pragma once
#include "XEngine/Scene/Entity.h"
namespace XEngine
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}
		// Get Component
		template<typename Component>
		Component& GetComponent() { return m_Entity.GetComponent<Component>(); }
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep timestep) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};
}

// byjohnmichael

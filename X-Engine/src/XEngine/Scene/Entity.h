#pragma once
#include <entt.hpp>
#include "XEngine/Scene/Scene.h"
#include "XEngine/Debug/Logging.h"
namespace XEngine
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		// Add Component
		template<typename Component, typename... Args>
		Component& AddComponent(Args&&... args)
		{
			XCORE_ASSERT(!HasComponent<Component>(), "Entity already has component");
			Component& component = m_Scene->m_Registry.emplace<Component>(m_EntityHandle, std::foward<Args>(args)...);
			m_Scene->OnComponentAdded<Component>(*this, component);
			return component;
		}
		// Get Component
		template<typename Component>
		Component& GetComponent()
		{
			XCORE_ASSERT(HasComponent<Component>(), "Entity does not component");
			return m_Scene->m_Registry.get<Component>(m_EntityHandle);
		}
		// Remove Component
		template<typename Component>
		void RemoveComponent()
		{
			XCORE_ASSERT(HasComponent<Component>(), "Entity does not component");
			m_Scene->m_Registry.remove<Component>(m_EntityHandle);
		}
		// Has Component
		template<typename Component>
		bool HasComponent()
			{ return m_Scene->m_Registry.has<Component>(m_EntityHandle); }
		operator bool() const
			{ return m_EntityHandle != entt::null; }
		operator entt::entity() const
			{ return m_EntityHandle; }
		operator uint32_t() const
			{ return (uint32_t)m_EntityHandle; }
		bool operator==(const Entity& other) const
			{ return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }
		bool operator!=(const Entity& other) const
			{ return !(*this == other); }
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}

// byjohnmichael

#include <ImGui/imgui.h>
#include "Panels/Hierarchy.h"
#include <glm/gtc/type_ptr.hpp>
#include "XEngine/Scene/Components.h"
namespace XEngine
{
	Hierarchy::Hierarchy(const Ref<Scene>& context)
		{ SetContext(context); }
	void Hierarchy::SetContext(const Ref<Scene>& context)
		{ m_Context = context; }
	void Hierarchy::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity { entityID, m_Context.get() };
			DrawEntityNode(entity);
		});
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};
		// Right-Click on a blank space
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");
			ImGui::EndPopup();
		}
		ImGui::End();
	}
	void Hierarchy::DrawEntityNode(Entity entity)
	{
		if (!entity.HasComponent<TagComponent>())
			entity.AddComponent<TagComponent>();
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
			m_SelectionContext = entity;
		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;
			ImGui::EndPopup();
		}
		if (opened)
		{
			ImGuiTreeNodeFlags falgs = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)465454, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}
}
#include <ImGui/imgui.h>
#include "Panels/Details.h"
#include <glm/gtc/type_ptr.hpp>
#include <ImGui/imgui_internal.h>
#include "XEngine/Scene/Components.h"
namespace XEngine
{
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
		// X
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		// Y
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		// Z
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}
	template<typename Component, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<Component>())
		{
			auto& component = entity.GetComponent<Component>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(Component).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
				ImGui::OpenPopup("ComponentSettings");
			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;
				ImGui::EndPopup();
			}
			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}
			if (removeComponent)
				entity.RemoveComponent<Component>();
		}
	}
	void Details::OnImGuiRender(Entity& m_SelectionContext)
	{
		ImGui::Begin("Details");
		if (m_SelectionContext)
		{
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;
			// Tag Component
			if (m_SelectionContext.HasComponent<TagComponent>())
			{
				auto& tag = m_SelectionContext.GetComponent<TagComponent>().Tag;
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), tag.c_str());
				if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
					tag = std::string(buffer);
			}
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");
			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			ImGui::PopItemWidth();
			// Transform Component
			DrawComponent<TransformComponent>("Transform", m_SelectionContext, [](auto& component)
			{
				DrawVec3Control("Position", component.Position);
				glm::vec3 rotation = glm::degrees(component.Rotation);
				DrawVec3Control("Rotation", rotation);
				component.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.Scale);
			});
			// Camera Component
			DrawComponent<CameraComponent>("Camera", m_SelectionContext, [](auto& component)
			{
				auto& camComp = component.Camera;
				ImGui::Checkbox("Primary", &component.Primary);
				const char* projectionTypeStrings[] = { "Orthographic", "Perspective" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camComp.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camComp.SetProjectionType((SceneCamera::ProjectionType)i);
						}
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				if (camComp.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					// Size
					float orthoSize = camComp.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camComp.SetOrthographicSize(orthoSize);
					// Near Clip
					float nearClip = camComp.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near Clip", &nearClip))
						camComp.SetOrthographicNearClip(nearClip);
					// Far Clip
					float farClip = camComp.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far Clip", &farClip))
						camComp.SetOrthographicFarClip(farClip);
					ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
				}
				if (camComp.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					// FOV
					float perspFOV = glm::degrees(camComp.GetPerspectiveFOV());
					if (ImGui::DragFloat("FOV", &perspFOV))
						camComp.SetPerspectiveFOV(glm::radians(perspFOV));
					// Near Clip
					float nearClip = camComp.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near Clip", &nearClip))
						camComp.SetPerspectiveNearClip(nearClip);
					// Far Clip
					float farClip = camComp.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far Clip", &farClip))
						camComp.SetPerspectiveFarClip(farClip);
				}
			});
			// Sprite Renderer Component
			DrawComponent<SpriteRendererComponent>("Sprite Renderer", m_SelectionContext, [](auto& component)
				{ ImGui::ColorEdit4("Color", glm::value_ptr(component.Color)); });
		}
		ImGui::End();
	}
}
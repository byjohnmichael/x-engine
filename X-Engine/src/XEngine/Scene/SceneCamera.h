#pragma once
#include "XEngine/Renderer/CameraSystem/Cameras.h"
namespace XEngine
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Orthographic = 0, Perspective = 1 };
		SceneCamera();
		virtual ~SceneCamera() = default;
		void SetOrthographic(float size, float nearClip, float farClip);
		void SetPerspective(float FOV, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);
		float GetOrthographicSize() const
			{ return m_OrthographicSize; }
		// Orthographic Camera Methods
		void SetOrthographicSize(float size)
		{
			m_OrthographicSize = size;
			RecalculateProjection();
		}
		// Near Clip
		float GetOrthographicNearClip() const
			{ return m_OrthographicNear; }
		void SetOrthographicNearClip(float nearClip)
		{
			m_OrthographicNear = nearClip;
			RecalculateProjection();
		}
		// Far Clip
		float GetOrthographicFarClip() const
			{ return m_OrthographicFar; }
		void SetOrthographicFarClip(float farClip)
		{
			m_OrthographicFar = farClip;
			RecalculateProjection();
		}
		// Perspective Camera Methods
		float GetPerspectiveFOV() const
			{ return m_PerspectiveFOV; }
		void SetPerspectiveFOV(float FOV)
		{
			m_PerspectiveFOV = FOV;
			RecalculateProjection();
		}
		// Near Clip
		float GetPerspectiveNearClip() const
			{ return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip)
		{
			m_PerspectiveNear = nearClip;
			RecalculateProjection();
		}
		// Far Clip
		float GetPerspectiveFarClip() const
			{ return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip)
		{
			m_PerspectiveFar = farClip;
			RecalculateProjection();
		}
		// Projection Type
		ProjectionType GetProjectionType() const
			{ return m_ProjectionType; }
		void SetProjectionType(ProjectionType type)
			{ m_ProjectionType = type; RecalculateProjection(); }
	private:
		// Functions
		void RecalculateProjection();
		// Members
		// Orthographic
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
		// Perspective
		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = .01f, m_PerspectiveFar = 1000.0f;
		float m_AspectRatio = 0.0f;
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
	};
}
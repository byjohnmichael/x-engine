// Controller for camera to move and zoom in and out
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/Renderer/CameraSystem/Cameras.h"
namespace XEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);
		void OnResize(float width, float height);
		OrthographicCamera& GetCamera()
			{ return m_Camera; }
		const OrthographicCamera& GetCamera() const
			{ return m_Camera; }
		float GetZoomLevel()
			{ return m_ZoomLevel; }
		void SetZoomLevel(float level)
			{ m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_RotationOn;
		glm::vec3 m_Position = {0,0,0};
		float m_Rotation = 0.0f;
		float m_Speed = 1.0f, m_RotationSpeed = 1.0f;
	};
}

// byjohnmichael

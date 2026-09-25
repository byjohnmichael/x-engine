// Camera Controller Source file
#include "Xpch.h"
#include "XEngine/Core/Input.h"
#include "XEngine/Core/KeyCodes.h"
#include "XEngine/Renderer/CameraSystem/CameraControllers.h"
namespace XEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : m_AspectRatio(aspectRatio), m_RotationOn(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {}
	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		XPROFILE_FUNCTION();
		if (Input::IsKeyPressed(Key::W))
		{
			m_Position.x += -sin(glm::radians(m_Rotation)) * m_Speed * timestep;
			m_Position.y += cos(glm::radians(m_Rotation)) * m_Speed * timestep;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_Position.x -= -sin(glm::radians(m_Rotation)) * m_Speed * timestep;
			m_Position.y -= cos(glm::radians(m_Rotation)) * m_Speed * timestep;
		}
		if (Input::IsKeyPressed(Key::D))
		{
			m_Position.x += cos(glm::radians(m_Rotation)) * m_Speed * timestep;
			m_Position.y += sin(glm::radians(m_Rotation)) * m_Speed * timestep;
		}
		else if (Input::IsKeyPressed(Key::A))
		{
			m_Position.x -= cos(glm::radians(m_Rotation)) * m_Speed * timestep;
			m_Position.y -= sin(glm::radians(m_Rotation)) * m_Speed * timestep;
		}
		m_Camera.SetPosition(m_Position);
		if (m_RotationOn)
		{
			if (Input::IsKeyPressed(Key::E))
				m_Rotation += m_RotationSpeed * timestep;
			else if (Input::IsKeyPressed(Key::Q))
				m_Rotation -= m_RotationSpeed * timestep;
			if (m_Rotation > 180.0f)
				m_Rotation -= 360.0f;
			else if (m_Rotation <= -180.0f)
				m_Rotation += 360.0f;
			m_Camera.SetRotation(m_Rotation);
		}
		m_Speed = m_ZoomLevel;
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		XPROFILE_FUNCTION();
		EventDispatcher dispacter(e);
		dispacter.Dispatch<MouseScrolledEvent>(XBIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispacter.Dispatch<WindowResizeEvent>(XBIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}
	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		XPROFILE_FUNCTION();
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, .25f);
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		XPROFILE_FUNCTION();
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}

// byjohnmichael

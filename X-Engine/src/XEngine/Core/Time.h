// Header file for Time class
#pragma once
namespace XEngine
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : m_DeltaTime(time) {}
		operator float()
			{ return m_DeltaTime; }
		float GetSeconds() const
			{ return m_DeltaTime; }
		float GetMilliseconds() const 
			{ return m_DeltaTime * 1000.0f; }
	private:
		float m_DeltaTime;
	};
}

// byjohnmichael

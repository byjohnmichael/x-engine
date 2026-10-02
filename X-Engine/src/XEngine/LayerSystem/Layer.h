// Layer Class Header file
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/Core/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnImGuiRender() = 0;
		virtual void OnAttach() 
			{ XCORE_INFO("{0} attached", GetName()); }
		virtual void OnDetach() 
			{ XCORE_INFO("{0} detached", GetName()); }
		virtual void OnUpdate(Timestep timestep) { }
		virtual void OnEvent(Event& event) {}
		const std::string& GetName() const
			{ return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

// byjohnmichael

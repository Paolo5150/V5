#pragma once
#include "../Dll.h"
#include <string>
#include <V5/Event/Event.h>

namespace V5Core
{

	class V5_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_DebugName(name) {};
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
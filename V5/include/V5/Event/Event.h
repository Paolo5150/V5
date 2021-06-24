#pragma once

namespace V5Core
{
	enum class  EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus,
		KeyDown, KeyHold,
		MouseBtnClick, MouseBtnHold
		
	};

	/**
	This type of Event (and subclasses) is intended to be used by a single listener, which will pass the event around accordingly
	*/
	class V5_API Event
	{
	public:
		Event(EventType type) : m_type(type) {}
		EventType GetType() { return m_type; }
		void Consume() { m_consumed = true; }
		bool GetIsConsumed() { return m_consumed; }
		virtual ~Event() {};
	protected:
		bool m_consumed = false;
		EventType m_type;

	};
}

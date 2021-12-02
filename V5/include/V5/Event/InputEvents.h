#pragma once
#include "Event.h"
#include <V5/Core/KeyCodes.h>

namespace V5Core
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(KeyCode kc) : Event(EventType::KeyDown), m_keyCode(kc) {}
	private:
		KeyCode m_keyCode;

	};

	class KeyHoldEvent : public Event
	{
	public:
		KeyHoldEvent(KeyCode kc) : Event(EventType::KeyHold), m_keyCode(kc) {}
	private:
		KeyCode m_keyCode;
	};

	class MouseBtnClickEvent : public Event
	{
	public:
		MouseBtnClickEvent(int btn) : Event(EventType::MouseBtnClick), m_btn(btn) {}
	private:
		int m_btn;

	};

	class MouseBtnHoldEvent : public Event
	{
	public:
		MouseBtnHoldEvent(int btn) : Event(EventType::MouseBtnHold), m_btn(btn) {}
	private:
		int m_btn;

	};

}

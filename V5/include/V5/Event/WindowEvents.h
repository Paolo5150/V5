#pragma once
#include "Event.h"
#include "../Dll.h"

namespace V5Core
{
	class V5_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() : Event(EventType::WindowClose) {}
		
	};

	class V5_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int nWidth, int nHeight) : Event(EventType::WindowResize),
			m_width(nWidth),
			m_height(nHeight)
		{
		}

	private:
		int m_width;
		int m_height;
	};

	class V5_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool isFocused) : Event(EventType::WindowFocus),
			m_isFocused(isFocused)
		{
		}

	private:
		bool m_isFocused;
	};
}

#pragma once
#include "Event.h"

namespace V5Core
{
	class WindowOpenEvent : public Event
	{
	public:
		WindowOpenEvent(int nWidth, int nHeight) : Event(EventType::WindowOpen),
			m_width(nWidth),
			m_height(nHeight) {}

		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

	private:
		int m_width;
		int m_height;

	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() : Event(EventType::WindowClose) {}
		
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int nWidth, int nHeight) : Event(EventType::WindowResize),
			m_width(nWidth),
			m_height(nHeight)
		{
		}

		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

	private:
		int m_width;
		int m_height;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool isFocused) : Event(EventType::WindowFocus),
			m_isFocused(isFocused)
		{
		}

		bool IsFocused() { return m_isFocused; }
	private:
		bool m_isFocused;
	};
}

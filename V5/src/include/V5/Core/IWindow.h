#pragma once
#include "../Dll.h"
#include <string>

namespace V5Core
{
	class IWindowListener;

	class V5_API IWindow
	{
	public:
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual std::string GetTitle() = 0;

		virtual void Update() = 0;
		virtual void Refresh() = 0;
		virtual void RegisterWindowListener(IWindowListener& listener) = 0;
		virtual bool IsQuitRequested() = 0;
	};
}
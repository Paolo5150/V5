#include "AndroidWindow.h"
#include <V5/Core/Logger.h>
#include <V5/Core/ICore.h>
#include <V5/Core/Factory.h>
#include <V5/Event/WindowEvents.h>
using namespace V5Core;


AndroidWindow::AndroidWindow(int width, int height, const std::string& title, void* windowCallback) :
	m_androidWindowCallback((AndroidWindowCallbacks*)windowCallback) ,
	m_width(width),
	m_height(height)
{
	V5LOG_INFO("Init display {0} {1}", m_width, m_height);

	m_androidWindowCallback->OnAcceleratorChange = [](int32_t& x, int32_t& y) 
	{
		V5LOG_INFO("Tap {0} {1}", x, y);
	};

	m_androidWindowCallback->OnWindowClose = []() 
	{
		WindowCloseEvent wce;
		V5Core::Factory().GetCore().TriggerEvent(wce);
	};


}

AndroidWindow::~AndroidWindow() {}




void AndroidWindow::Update() 
{
	if(m_androidWindowCallback != nullptr)
		m_androidWindowCallback->PollEvents(); 

}

void AndroidWindow::RegisterEventListener(std::function<void(Event&)> listener) {} ///< Intended for a single, main listener
void AndroidWindow::Refresh() 
{ 
	m_androidWindowCallback->Refresh();
}

void AndroidWindow::MaximizeWindow() {}
void AndroidWindow::Destroy() 
{
	m_androidWindowCallback->CloseWindow();
	m_androidWindowCallback = nullptr;
}

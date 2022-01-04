#include "AndroidWindow.h"
#include <V5/Core/Logger.h>
using namespace V5Core;

void OnAccelerometerChange(int32_t& x, int32_t& y)
{
	V5LOG_INFO("Tap {0} {1}", x, y);
}

AndroidWindow::AndroidWindow(int width, int height, const std::string& title, void* windowCallback) :
	m_androidWindowCallback((AndroidWindowCallbacks*)windowCallback)
{
	m_androidWindowCallback->OnAcceleratorChange = OnAccelerometerChange;
}

AndroidWindow::~AndroidWindow() {}




void AndroidWindow::Update() 
{
	if(m_androidWindowCallback != nullptr)
		m_androidWindowCallback->PollEvents(); 

}

void AndroidWindow::RegisterEventListener(std::function<void(Event&)> listener) {} ///< Intended for a single, main listener
void AndroidWindow::Refresh() {}

void AndroidWindow::MaximizeWindow() {}
void AndroidWindow::Destroy() {}

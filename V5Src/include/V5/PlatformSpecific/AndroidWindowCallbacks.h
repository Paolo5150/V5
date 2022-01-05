#pragma
#include <functional>

struct AndroidWindowCallbacks
{
	void (*PollEvents)();
	void (*CloseWindow)();
	void (*Refresh)();

	/*
	* Called when user presses screen, returns x Y screen coordinate
	*/
	void (*OnAcceleratorChange)(int32_t& x, int32_t& y);

	/*
	* Called when screen is being closed or hidden
	*/
	void (*OnWindowClose)();

};
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
	void (*OnSingleTap)(int32_t x, int32_t y);
	void (*OnTap)(int32_t id, int32_t x, int32_t y);
	void (*OnTapRelease)(int32_t id, int32_t x, int32_t y);
	void (*OnPointerMove)(int32_t id, int32_t x, int32_t y);
	int (*OnBackButtonPressed)();

	/*
	* Called when screen is being closed or hidden
	*/
	void (*OnWindowClose)();

};
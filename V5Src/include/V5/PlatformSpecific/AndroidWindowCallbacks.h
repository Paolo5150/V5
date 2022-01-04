#pragma
#include <functional>

struct AndroidWindowCallbacks
{
	void (*PollEvents)();
	void (*CloseWindow)();

	void (*OnAcceleratorChange)(int32_t& x, int32_t& y);

};
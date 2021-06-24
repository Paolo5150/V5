#pragma once

#include "../Dll.h"

namespace V5Core
{

class V5_API ITime
{
public:
	virtual double GetLooseDeltaTimeSeconds() = 0;
	virtual double GetDeltaTimeSeconds() = 0;
};
}
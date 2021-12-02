#pragma once

namespace V5Core
{
class ITime
{
public:
	virtual double GetLooseDeltaTimeSeconds() = 0;
	virtual double GetDeltaTimeSeconds() = 0;
};
}
#include "HitStop.h"



HitStop::HitStop() : _stopTime(0)
{
}


HitStop::~HitStop()
{
}

void
HitStop::Update()
{
	if (_stopTime < 0)
	{
		_stopTime = 0;
		return;
	}
	--_stopTime;
}

void 
HitStop::HitStopTime(float stopTime)
{
	_stopTime = stopTime;
}

bool 
HitStop::IsHitStop()
{
	return _stopTime > 0;
}
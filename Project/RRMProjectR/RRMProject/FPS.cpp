#include "FPS.h"
#include <RRMLib.h>


FPS::FPS() : _startTime(0), _count(0), _fps(0)
{
}


FPS::~FPS()
{
}


void 
FPS::Update()
{
	if (_count == 0)
	{
		_time.Start();
		_startTime = _time.GetTimes().millisec;
	}
	if (_count == FRAME_NUM)
	{
		int t = _time.GetTimes().millisec;
		_fps = 1000.0f / ((t - _startTime) / (float)FRAME_NUM);
		_count = 0;
		_startTime = t;
	}
	++_count;
}

void 
FPS::Draw()
{
	char titleBar[32];
	titleBar[0] = '\0';
	sprintf(titleBar, "%.1f", _fps);

	RRMLib::SetMainWindowText(titleBar);
}
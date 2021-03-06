#include "GameTime.h"
#include "Timer.h"


GameTime::GameTime()
{
	_deltaTime = 1.0f;
	_timeScale = 1.0f;
}

GameTime::~GameTime()
{
}

//時間の係数を変更
//0.0f 〜 2.0fで指定
void 
GameTime::SetTimeScale(float scale)
{
	if (scale > 2.0f)
	{
		_timeScale = 2.0f;
	}
	else if (scale < 0.0f)
	{
		_timeScale = 0.0f;
	}
	_timeScale = scale;

	for (auto& t : _timeScales)
	{
		t.second.timeScale = _timeScale;
		t.second.isStartUp = true;
	}
}

void
GameTime::SetTimeScale(float scale, Object* other)
{
	if (scale > 2.0f)
	{
		_timeScales[other].timeScale = 2.0f;
		return;
	}
	else if(scale < 0.0f)
	{
		_timeScales[other].timeScale = 0.0f;
		return;
	}
	_timeScales[other].timeScale = scale;
	_timeScales[other].isStartUp = true;
}

const float& 
GameTime::GetTimeScale()
{
	return _timeScale;
}

const float& 
GameTime::GetTimeScale(Object* other)
{
	if (!_timeScales[other].isStartUp)
	{
		_timeScales[other].isStartUp = true;
		_timeScales[other].timeScale = 1.0f;
		_timeScales[other].stopTime = 0.0f;
		_timeScales[other].isSlow = false;
	}
	return _timeScales[other].timeScale;
}
void 
GameTime::BeginUpdate()
{
	_time.Start();
}
void 
GameTime::EndUpdate()
{
	Times t = _time.GetTimes();
}

const float& 
GameTime::GetDeltaTime()
{
	return _deltaTime;
}

TimeData& 
GameTime::GetTimeData(Object* other)
{
	return _timeScales[other];
}

std::map<Object*, TimeData>& 
GameTime::GetTimeScaleList()
{
	return _timeScales;
}
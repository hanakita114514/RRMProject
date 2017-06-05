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


//ŽžŠÔ‚ÌŒW”‚ð•ÏX
//0.0f ` 1.0f‚ÅŽw’è
void 
GameTime::SetTimeScale(float scale)
{
	_timeScale = scale;
	if (scale > 1.0f)
	{
		_timeScale = 1.0f;
	}
	else if(scale < 0.0f)
	{
		_timeScale = 0.0f;
	}

}
const float& 
GameTime::GetTimeScale()
{
	return _timeScale;
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
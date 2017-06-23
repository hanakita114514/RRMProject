#include "SlowDown.h"
#include "GameTime.h"


SlowDown::SlowDown()
{
	_slowTime = 0;
	_time = 0;
	_isSlow = false;
	_resio = 1.0f;
}


SlowDown::~SlowDown()
{

}

void 
SlowDown::Update()
{
	//if (_slowTime < _time)
	//{
	//	_time = 0;
	//	_isSlow = false;
	//	GameTime::Instance().SetTimeScale(1.0f);
	//}
	//++_time;

	////スローモーション状態
	//if (_isSlow)
	//{
	//	GameTime::Instance().SetTimeScale(_resio);
	//	return;
	//}


	//GameTime::Instance().SetTimeScale(_resio);

	for (auto& td : GameTime::Instance().GetTimeScaleList())
	{
		if (!td.second.isSlow)
		{
			continue;
		}

		//GameTime::Instance().SetTimeScale(td.second.timeScale, td.first);

		if (td.second.stopTime <= 0)
		{
			td.second.timeScale = 1.0f;
			td.second.isSlow = false;
		}

		--td.second.stopTime;
	}
}

void 
SlowDown::SlowMotion(int time)
{
	_isSlow = true;
	_slowTime = time;
	_resio = 0.5f;
}

void 
SlowDown::SlowMotion(int time, Object* other)
{
	TimeData& td = GameTime::Instance().GetTimeData(other);
	td.isSlow = true;
	td.stopTime = time;
	td.timeScale = 0.5f;
	td.isStartUp = true;
}

void
SlowDown::TheWorld(int time)
{
	_isSlow = true;
	_slowTime = time;
	_resio = 0.0f;
}

void 
SlowDown::TheWorld(int time, Object* other)
{

}
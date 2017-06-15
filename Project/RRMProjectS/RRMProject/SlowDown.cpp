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
	//�X���[���[�V������Ԃł͂Ȃ��Ƃ�
	if (!_isSlow)
	{
		GameTime::Instance().SetTimeScale(1.0f);
		return;
	}


	GameTime::Instance().SetTimeScale(_resio);

	if (_slowTime < _time)
	{
		_time = 0;
		_isSlow = false;
	}
	++_time;
}

void 
SlowDown::SlowMotion(int time)
{
	_isSlow = true;
	_slowTime = time;
	_resio = 0.5f;
}

void
SlowDown::TheWorld(int time)
{
	_isSlow = true;
	_slowTime = time;
	_resio = 0.0f;
}
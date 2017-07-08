#include "Result.h"
#include <RRMLib.h>
#include "common.h"
#include "Logo.h"


Result::Result()
{
	_handle = RRMLib::LoadGraph("Resource/img/BackGround/fade.png");

	int logoHandle = RRMLib::LoadGraph("Resource/img/UI/Result2.png");

	_update[State::start] = &Result::StartUpdate;
	_update[State::middle] = &Result::MiddleUpdate;
	_update[State::end] = &Result::EndUpdate;
	_state = State::start;

	_logo = new Logo(logoHandle, Position(WINDOW_WIDTH / 2, 100));
}


Result::~Result()
{
	delete _logo;
}

void 
Result::StartUpdate()
{
	_endCall.Update();

	if (_endCall.IsEnd())
	{
		_state = State::middle;
	}
}

void
Result::MiddleUpdate()
{
	_endCall.Update();
	_logo->Update();
}

void 
Result::EndUpdate()
{

}

void 
Result::Update()
{
	(this->*_update[_state])();
}
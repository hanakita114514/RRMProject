#include "Result.h"
#include <RRMLib.h>
#include "common.h"


Result::Result()
{
	_handle = RRMLib::LoadGraph("Resource/img/BackGround/fade.png");

	_update[State::start] = &Result::StartUpdate;
	_update[State::end] = &Result::EndUpdate;
	_state = State::start;
}


Result::~Result()
{
}

void 
Result::StartUpdate()
{
	_endCall.Update();
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
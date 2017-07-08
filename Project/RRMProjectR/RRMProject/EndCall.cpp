#include "EndCall.h"
#include <RRMLib.h>
#include "common.h"
#include "Logo.h"

static const float FILTER_H = 96.0f;
static const float SPEED = 4.0f;

EndCall::EndCall()
{
	int logoHandle;
	_filterHandle = RRMLib::LoadGraph("Resource/img/BackGround/fade.png");
	logoHandle = RRMLib::LoadGraph("Resource/img/UI/Finished.png");

	_state = State::start;
	_update[State::start] = &EndCall::StartUpdate;
	_update[State::middle] = &EndCall::MiddleUpdate;
	_update[State::startWait] = &EndCall::StartWaitUpdate;
	_update[State::end] = &EndCall::EndUpdate;

	_height = 0.0f;

	_logo = new Logo(logoHandle, Position(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	_frame = 0;
}


EndCall::~EndCall()
{
	delete _logo;
}

void
EndCall::StartUpdate()
{
	_height += SPEED;
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT / 2 - _height / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 + _height / 2, _filterHandle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);

	_logo->Update();

	if (_height >= FILTER_H)
	{
		_height = FILTER_H;
		if (_logo->IsEnd())
		{
			_state = State::startWait;
		}
	}
}
void
EndCall::StartWaitUpdate()
{
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT / 2 - _height / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 + _height / 2, _filterHandle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);

	_logo->Update();
	if (_frame >= 30)
	{
		_state = State::middle;
		_frame = 0;
	}
	++_frame;
}
void 
EndCall::MiddleUpdate()
{
	_height += SPEED * 4;

	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT / 2 - _height / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 + _height / 2, _filterHandle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);
	_logo->Update();

	if (_height >= WINDOW_HEIGHT)
	{
		_height = WINDOW_HEIGHT;
		_state = State::end;
	}

}
void 
EndCall::EndUpdate()
{
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT / 2 - _height / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 + _height / 2, _filterHandle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);
}

void
EndCall::Update()
{
	(this->*_update[_state])();
}
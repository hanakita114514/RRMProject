#include "EndCall.h"
#include <RRMLib.h>
#include "common.h"

static const float FILTER_H = 64.0f;

EndCall::EndCall()
{
	_filterHandle = RRMLib::LoadGraph("Resource/img/BackGround/fade.png");

	_state = State::start;
	_update[State::start] = &EndCall::StartUpdate;
	_update[State::end] = &EndCall::EndUpdate;
}


EndCall::~EndCall()
{
}

void
EndCall::StartUpdate()
{
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT / 2 - FILTER_H / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 + FILTER_H / 2, _filterHandle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);
}
void 
EndCall::EndUpdate()
{

}

void
EndCall::Update()
{

}
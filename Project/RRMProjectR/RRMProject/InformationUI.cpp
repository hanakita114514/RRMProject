#include "InformationUI.h"
#include <RRMLib.h>
#include "common.h"

static const float FILTER_H = 32.0f;
static const float OFFSET_Y = 8.f;

InformationUI::InformationUI() : _fps(Position(WINDOW_WIDTH - 150.0f, WINDOW_HEIGHT - 25.0f), 40.f)
{
	_filterHandle = RRMLib::LoadGraph("Resource/img/BackGround/fade.png");
}


InformationUI::~InformationUI()
{
	RRMLib::DeleteGraph(_filterHandle);
}

void
InformationUI::Draw()
{
	_fps.Update();
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	RRMLib::DrawExtendGraph(0,WINDOW_HEIGHT - FILTER_H - OFFSET_Y, WINDOW_WIDTH, WINDOW_HEIGHT - OFFSET_Y, _filterHandle, true, false);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);
	_fps.Draw();
}
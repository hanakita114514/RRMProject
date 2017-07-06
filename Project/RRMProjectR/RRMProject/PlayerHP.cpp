#include "PlayerHP.h"
#include <RRMLib.h>
#include "GraphicLoad.h"
#include "common.h"

static const float HPBAR_MAX = 140.0f;

static const float HPBAR_HEIGHT = 15.0f;

static const float BAR_INIT_X = 68.0f;
static const float BAR_INIT_Y = 55.0f;

PlayerHP::PlayerHP()
{
	_hpBarHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/hebi_HPbar.png");
	_gaugeHandle[0] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/hebi_HP.png");
	_gaugeHandle[1] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/hebi_HP2.png");
	_gaugeHandle[2] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/hebi_HP3.png");

	_barPos.x = 0;
	_barPos.y = -20;

	_offset = HPBAR_MAX;
	_backOffset = HPBAR_MAX;
	_offsetBuf = HPBAR_MAX;

	_commitFrame = 0;
}


PlayerHP::~PlayerHP()
{
}


void 
PlayerHP::Update()
{
	++_commitFrame;
	_backOffset -= 0.5f;
	if (_offsetBuf >= _backOffset)
	{
		_backOffset = _offsetBuf;
	}
}

void 
PlayerHP::Commit()
{
	_backOffset = _offsetBuf;
	_offsetBuf = _offset;
}

void
PlayerHP::CommitPeriod()
{
	if (_commitFrame % 30 == 0)
	{
		Commit();
	}
}

void
PlayerHP::Draw(HitPoint& hp)
{
	float offsetX = HPBAR_MAX * (hp.GetHitPoint() / hp.GetMaxHP());
	if (offsetX < 0.f)
	{
		offsetX = 0.f;
	}
	else if (offsetX > HPBAR_MAX)
	{
		offsetX = HPBAR_MAX;
	}

	_offset = offsetX;

	RRMLib::DrawExtendGraph(_barPos.x + BAR_INIT_X, _barPos.y + BAR_INIT_Y, _barPos.x + BAR_INIT_X + HPBAR_MAX, _barPos.y + BAR_INIT_Y + HPBAR_HEIGHT, _gaugeHandle[2]);
	RRMLib::DrawExtendGraph(_barPos.x + BAR_INIT_X, _barPos.y + BAR_INIT_Y, _barPos.x + BAR_INIT_X + _backOffset, _barPos.y + BAR_INIT_Y + HPBAR_HEIGHT, _gaugeHandle[1]);
	RRMLib::DrawExtendGraph(_barPos.x + BAR_INIT_X, _barPos.y + BAR_INIT_Y, _barPos.x + BAR_INIT_X + offsetX, _barPos.y + BAR_INIT_Y + HPBAR_HEIGHT, _gaugeHandle[0]);
	RRMLib::DrawGraph(_barPos.x, _barPos.y, _hpBarHandle);
}
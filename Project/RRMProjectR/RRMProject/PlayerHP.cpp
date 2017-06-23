#include "PlayerHP.h"
#include <RRMLib.h>
#include "GraphicLoad.h"
#include "common.h"

const float HPBAR_MAX = 140.0f;

const float HPBAR_HEIGHT = 15.0f;

const float BAR_INIT_X = 68.0f;
const float BAR_INIT_Y = 55.0f;

PlayerHP::PlayerHP()
{
	_hpBarHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/hebi_HPbar.png");
	_gaugeHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/hebi_HP.png");

	_barPos.x = 30;
	_barPos.y = WINDOW_HEIGHT - 120;
}


PlayerHP::~PlayerHP()
{
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

	RRMLib::DrawExtendGraph(_barPos.x + BAR_INIT_X, _barPos.y + BAR_INIT_Y, _barPos.x + BAR_INIT_X + offsetX, _barPos.y + BAR_INIT_Y + HPBAR_HEIGHT, _gaugeHandle);
	RRMLib::DrawGraph(_barPos.x, _barPos.y, _hpBarHandle);
}
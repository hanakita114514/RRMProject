#include "HPBar.h"
#include "DxLib.h"


const float HPBAR_MAX = 28.0f;
const float INIT_BAR_POS = 2.0f;

HPBar::HPBar(const Position& ownPos, HitPoint& hp) : 
	_ownPos(ownPos), _hp(hp)
{
	_barHandle = DxLib::LoadGraph("Resource/img/UI/bar.png");
	_gaugeHandle = DxLib::LoadGraph("Resource/img/UI/gauge.png");

	_barPos = Vector2(0, 0);
}


HPBar::~HPBar()
{
}

void
HPBar::Draw()
{
	//DxLib::DrawExtendGraph(12, 10, 40, 16, _gaugeHandle, true);
	//DxLib::DrawGraph(10, 10, _barHandle, true);
	_barPos = Vector2(_ownPos.x, _ownPos.y - 5);

	float offsetX = HPBAR_MAX * ( _hp.GetHitPoint() / _hp.GetMaxHP());
	if (offsetX < 0.f)
	{
		offsetX = 0.f;
	}
	else if (offsetX > HPBAR_MAX)
	{
		offsetX = HPBAR_MAX;
	}

	DxLib::DrawExtendGraphF(_barPos.x + INIT_BAR_POS, _barPos.y, _barPos.x + INIT_BAR_POS + offsetX, _barPos.y + 6, _gaugeHandle, true);
	DxLib::DrawGraph(_barPos.x, _barPos.y, _barHandle, true);
}

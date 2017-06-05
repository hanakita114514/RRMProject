#include "HPBar.h"
#include "DxLib.h"
#include "GraphicLoad.h"

const float HPBAR_MAX = 28.0f;
const float INIT_BAR_POS = 2.0f;

HPBar::HPBar()
{
	_barHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/bar.png");
	_gaugeHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/gauge.png");

}


HPBar::~HPBar()
{
}

void
HPBar::Draw(const Position& pos, HitPoint& hp)
{
	//DxLib::DrawExtendGraph(12, 10, 40, 16, _gaugeHandle, true);
	//DxLib::DrawGraph(10, 10, _barHandle, true);

	float offsetX = HPBAR_MAX * ( hp.GetHitPoint() / hp.GetMaxHP());
	if (offsetX < 0.f)
	{
		offsetX = 0.f;
	}
	else if (offsetX > HPBAR_MAX)
	{
		offsetX = HPBAR_MAX;
	}

	DxLib::DrawExtendGraphF(pos.x + INIT_BAR_POS, pos.y, pos.x + INIT_BAR_POS + offsetX, pos.y + 6, _gaugeHandle, true);
	DxLib::DrawGraph(pos.x, pos.y, _barHandle, true);
}

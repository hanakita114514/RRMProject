#include "HPBar.h"
#include "RRMLib.h"
#include "GraphicLoad.h"

const float HPBAR_MAX = 28.0f;
const float INIT_BAR_POS = 2.0f;

HPBar::HPBar()
{
	_barHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/bar.png");
	_gaugeHandle[0] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/gauge.png");
	_gaugeHandle[1] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/gauge2.png");
	_gaugeHandle[2] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/gauge3.png");

	_offset = HPBAR_MAX;
	_backOffset = HPBAR_MAX;
	_offsetBuf = HPBAR_MAX;
}


HPBar::~HPBar()
{
}

void 
HPBar::Update()
{
	_backOffset -= 0.2f;
	if (_offsetBuf >= _backOffset)
	{
		_backOffset = _offsetBuf;
	}
}

void
HPBar::Commit()
{
	_backOffset = _offsetBuf;
	_offsetBuf = _offset;
}

void
HPBar::Draw(const Position& pos, HitPoint& hp)
{
	//RRMLib::DrawExtendGraph(12, 10, 40, 16, _gaugeHandle, true);
	//RRMLib::DrawGraph(10, 10, _barHandle, true);

	float offsetX = HPBAR_MAX * ( hp.GetHitPoint() / hp.GetMaxHP());
	if (offsetX < 0.f)
	{
		offsetX = 0.f;
	}
	else if (offsetX > HPBAR_MAX)
	{
		offsetX = HPBAR_MAX;
	}

	_offset = offsetX;

	RRMLib::DrawExtendGraph(pos.x + INIT_BAR_POS, pos.y, pos.x + INIT_BAR_POS + HPBAR_MAX, pos.y + 6, _gaugeHandle[2]);
	RRMLib::DrawExtendGraph(pos.x + INIT_BAR_POS, pos.y, pos.x + INIT_BAR_POS + _backOffset, pos.y + 6, _gaugeHandle[1]);
	RRMLib::DrawExtendGraph(pos.x + INIT_BAR_POS, pos.y, pos.x + INIT_BAR_POS + offsetX, pos.y + 6, _gaugeHandle[0]);
	RRMLib::DrawGraph(pos.x, pos.y, _barHandle);
}

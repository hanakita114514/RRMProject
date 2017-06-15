#include "Arrow.h"
#include "GraphicLoad.h"
#include "Rect.h"
#include <DxLib.h>

Arrow::Arrow()
{
	_arrowHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/Arrow_Smile.png");
	_width = ArrowWidth;
	_height = ArrowHeight;
}


Arrow::~Arrow()
{
}

void Arrow::Draw()
{
	DxLib::DrawGraph((int)_pos.x, (int)_pos.y, _arrowHandle, true);
}

void Arrow::SetPos(Position position)
{
	_pos.x = position.x - _width;
	_pos.y = position.y;
}

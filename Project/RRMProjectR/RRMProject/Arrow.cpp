#include "Arrow.h"
#include "GraphicLoad.h"
#include "Rect.h"
#include <RRMLib.h>

Arrow::Arrow()
{
	_arrowHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/RightArrow.png");
	_width = ArrowWidth;
	_height = ArrowHeight;
}


Arrow::~Arrow()
{
}

void Arrow::Draw()
{
	RRMLib::DrawGraph((int)_pos.x, (int)_pos.y, _arrowHandle, true);
}

void Arrow::Move(Vector2 velocity)
{
	_pos.y += velocity.y;
}

void Arrow::SetPos(Position position)
{
	_pos.x = position.x - _width;
	_pos.y = position.y;
}

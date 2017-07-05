#include "Mushroom.h"
#include <RRMLib.h>
#include "GameTime.h"

static const int IMG_NUM = 6;

static const float IMG_HEIGHT = 64.0f;
static const float IMG_WIDTH = 64.0f;

Mushroom::Mushroom(int handle, const Position& pos)
{
	_handle = handle;
	_rc.pos = pos;
	_rc.w = IMG_WIDTH;
	_rc.h = IMG_HEIGHT;

	_update = &Mushroom::AliveUpdate;
}

Mushroom::~Mushroom()
{
}

void 
Mushroom::Initialize()
{

}

void 
Mushroom::AliveUpdate()
{
	Gravity();

	if (_hp.IsDead())
	{
		_isAlive = false;
	}
}

void 
Mushroom::DyingUpdate()
{

}

void 
Mushroom::Update()
{
	Anim();
	(this->*_update)();
}

void 
Mushroom::Draw(const Vector2& offset)
{
	//RRMLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle);
	Position drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y, IMG_WIDTH, IMG_HEIGHT, _handle, true, false);
	_hpbar.Draw(Position(drawPos.x + _rc.w / 4, drawPos.y - _rc.h / 4), _hp);
}

void 
Mushroom::Anim()
{
	_animFrame += GameTime::Instance().GetTimeScale(this);

	static const Vector2 uv[IMG_NUM]
	{
		Vector2(IMG_WIDTH * 0,IMG_HEIGHT * 0),
		Vector2(IMG_WIDTH * 1,IMG_HEIGHT * 0),
		Vector2(IMG_WIDTH * 2,IMG_HEIGHT * 0),
		Vector2(IMG_WIDTH * 0,IMG_HEIGHT * 1),
		Vector2(IMG_WIDTH * 1,IMG_HEIGHT * 1),
		Vector2(IMG_WIDTH * 2,IMG_HEIGHT * 1),
	};

	unsigned int animIdx = (int)(_animFrame * 0.3f) % IMG_NUM;

	_uv = uv[animIdx];
}

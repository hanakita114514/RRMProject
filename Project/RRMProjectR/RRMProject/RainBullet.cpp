#include "RainBullet.h"

static const float GRAVITY = 0.072f;
static const int WAIT_TIME = 30;

RainBullet::RainBullet(int handle)
{
	_handle = handle;

	_update[State::start] = &RainBullet::StartUpdate;
	_update[State::fall] = &RainBullet::FallUpdate;
	_state = State::start;
}


RainBullet::~RainBullet()
{
}

void 
RainBullet::Initialize(const Position& pos, Vector2 vec, ObjectType type)
{
	_life = 500.f;
	_circle.pos = pos;
	//_vel = vec;
	_vec = vec;
	_objType = type;
	_vel = Vector2(_vec.x, 0);
	_repulsion = 1.0f;
	_startCnt = 0;
}

void 
RainBullet::StartUpdate()
{
	if (_startCnt > WAIT_TIME)
	{
		_state = State::fall;
	}
	++_startCnt;
}

void 
RainBullet::FallUpdate()
{
	_vel.y += GRAVITY;

	_circle.pos += _vel * GameTime::Instance().GetTimeScale(_owner);
}

void
RainBullet::Update()
{
	(this->*_update[_state])();

	LifeDecrease();

	if (_life <= 0.f)
	{
		Destory();
	}
}

void
RainBullet::Draw(const Vector2& offset)
{
	Circle cir;
	cir.pos = _circle.pos;
	cir.pos -= offset;
	cir.DrawGraph(_handle);
}

void
RainBullet::Hit(Block* other)
{
	_vel.y = -4.f * _repulsion;
	_vel.x = _vec.x * 2;

	_repulsion *= 0.8f;
}
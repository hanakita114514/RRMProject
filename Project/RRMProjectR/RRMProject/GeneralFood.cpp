#include "GeneralFood.h"
#include <RRMLib.h>


GeneralFood::GeneralFood(int handle, const Position& pos, const Vector2& vel, Food::FoodStatus status, double turnAngle)
{
	_handle = handle;
	_rc.pos = pos;
	_vel = vel;
	_rc.w = 32.f;
	_rc.h = 32.f;

	_fs = status;

	_score = 100;

	_update[State::normal] = &GeneralFood::NormalUpdate;
	_update[State::collect] = &GeneralFood::CollectUpdate;
	_state = State::normal;
}


GeneralFood::~GeneralFood()
{
}

void
GeneralFood::NormalUpdate()
{
	_rc.pos += _vel;
	DistanceAttenuation();
	Gravity();

	if (_collectFlag && _hitGround)
	{
		_state = State::collect;
	}
}

void
GeneralFood::CollectUpdate()
{
	_rc.pos += _vel;
}

void 
GeneralFood::Update()
{
	(this->*_update[_state])();
}

void 
GeneralFood::Draw(const Vector2& offset)
{
	RRMLib::DrawRotaGraph(_rc.Center().x, _rc.Center().y, _angle, _handle, true, false);
}
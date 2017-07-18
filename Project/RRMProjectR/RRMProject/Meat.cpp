#include "Meat.h"
#include <RRMLib.h>

Meat::Meat()
{
}


Meat::Meat(int handle)
{
	_handle = handle;

	_update = &Meat::AlliveUpdate;
	_meatState = State::wait;
}

Meat::~Meat()
{

}

void Meat::Initialize()
{

}

void Meat::Update()
{
	(this->*_update)();
	(this->*_state[(int)_meatState])();
}

void Meat::AlliveUpdate()
{

}

void Meat::DamageUpdate()
{

}

void Meat::Wait()
{

}

void Meat::Damage()
{
	_meatState = State::wait;
}

void Meat::Shot()
{
	_meatState = State::wait;
}

void Meat::Anim()
{

}

void Meat::Draw(const Vector2& offset)
{
	RRMLib::DrawGraph(_rc.pos.x + offset.x, _rc.pos.y + offset.y, _handle);
}

#include "Meat.h"
#include <RRMLib.h>

Meat::Meat()
{
}


Meat::Meat(int handle)
{
	_handle = handle;

	_update = &Meat::AlliveUpdate;
	_state = &Meat::Wait;
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
	(this->*_state)();
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
	_state = &Meat::Wait;
}

void Meat::Shot()
{
	_state = &Meat::Wait;
}

void Meat::Anim()
{

}

void Meat::Draw(const Vector2& offset)
{
	RRMLib::DrawGraph(_rc.pos.x + offset.x, _rc.pos.y + offset.y, _handle);
}

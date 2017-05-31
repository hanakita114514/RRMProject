#include "HitPoint.h"



HitPoint::HitPoint(int hp) : _hp(hp), _maxHp(hp)
{
}


HitPoint::~HitPoint()
{
}

void
HitPoint::SetMaxHp(int hp)
{
	_maxHp = hp;
	if (IsHpMax())
	{
		_hp = hp;
	}
}

void 
HitPoint::Recovery(int recval)
{
	_hp += recval;
	if (IsHpMax())
	{
		_hp = _maxHp;
	}
}

void 
HitPoint::Damage(int damage)
{
	_hp -= damage;
}

bool 
HitPoint::IsDead()
{
	if (_hp <= 0)
	{
		return false;
	}
	return false;
}

bool 
HitPoint::IsHpMax()
{
	if (_hp >= _maxHp)
	{
		return true;
	}
	return false;
}

float
HitPoint::GetHitPoint()
{
	return _hp;
}

float
HitPoint::GetMaxHP()
{
	return _maxHp;
}
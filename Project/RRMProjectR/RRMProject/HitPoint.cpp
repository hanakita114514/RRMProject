#include "HitPoint.h"



HitPoint::HitPoint(float hp) : _hp(hp), _maxHp(hp)
{
}


HitPoint::~HitPoint()
{
}

void
HitPoint::SetMaxHp(float hp)
{
	_maxHp = hp;
	if (IsHpMax())
	{
		_hp = hp;
	}
}

void 
HitPoint::Recovery(float recval)
{
	_hp += recval;
	if (IsHpMax())
	{
		_hp = _maxHp;
	}
}

void
HitPoint::FullRecovery()
{
	_hp = _maxHp;
}

void 
HitPoint::Damage(float damage)
{
	_hp -= damage;
}

bool 
HitPoint::IsDead()
{
	return _hp <= 0;
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
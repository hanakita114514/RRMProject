#include "Armor.h"
#include "GameTime.h"

//Ž©“®‰ñ•œ’l
const float gradually_recov = 0.5f;

Armor::Armor(float endurance) : _endurance(endurance), _enduranceMax(endurance), _waitTime(0)
{
}


Armor::~Armor()
{
}

void 
Armor::Recovery()
{
	_endurance = _enduranceMax;
}

void 
Armor::Damage(float damage)
{
	_endurance -= damage;
	_waitTime = 30;
}

void 
Armor::AutomaticRecovery()
{
	if (_waitTime < 0)
	{
		Recovery(gradually_recov * GameTime::Instance().GetTimeScale());
	}

	_waitTime -= 1 * GameTime::Instance().GetTimeScale();
}

void 
Armor::Recovery(float recoval)
{
	_endurance += recoval;

	if (_enduranceMax < _endurance)
	{
		_endurance = _enduranceMax;
		return;
	}
}

bool 
Armor::IsBroken()
{
	return _endurance <= 0;
}
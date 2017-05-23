#include "PowerPoint.h"


const unsigned int RECOVERY_TIME = 5;

PowerPoint::PowerPoint(int pp) : _pp(pp), _maxPP(pp), _recVal(1)
{
	_time.Start();
}


PowerPoint::~PowerPoint()
{
}

void 
PowerPoint::Update()
{
	if (_time.GetTime().seconds == RECOVERY_TIME)
	{
		_time.Reset();

		_pp += _recVal;

		if (IsPPMax())
		{
			_pp = _maxPP;
		}
	}
}

bool 
PowerPoint::Use()
{
	if (!IsAbsentPP())
	{
		_pp -= 1;
		return true;
	}
	return false;
}

int 
PowerPoint::GetPowerPoint()
{
	return _pp;
}

int
PowerPoint::GetMaxPP()
{
	return _maxPP;
}

void 
PowerPoint::SetMaxPP(const int& maxpp)
{
	_maxPP = maxpp;
	if (IsPPMax())
	{
		_pp = _maxPP;
	}
}

bool 
PowerPoint::IsPPMax()
{
	if (_pp >= _maxPP)
	{
		return true;
	}
	return false;
}

bool 
PowerPoint::IsAbsentPP()
{
	if (_pp <= 0)
	{
		return true;
	}
	return false;
}
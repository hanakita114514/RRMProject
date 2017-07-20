#include "PowerPoint.h"
#include <RRMLib.h>

static const unsigned int RECOVERY_TIME = 1;
static const float IMG_W = 16.0f;
static const float IMG_H = 16.0f;
static const float OFFSET = IMG_W + 2.0f;

PowerPoint::PowerPoint(int pp) : _pp(pp), _maxPP(pp), _recVal(1)
{
	_time.Start();

	_handle = RRMLib::LoadGraph("Resource/img/Player/SKILL.png");

	_pos = Position(50, 60);
}


PowerPoint::~PowerPoint()
{
}

void 
PowerPoint::Update()
{
	if (IsPPMax())
	{
		_time.Reset();
		return;
	}
	if (_time.GetTime().seconds >= RECOVERY_TIME)
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
	return _pp <= 0;
}

void 
PowerPoint::Draw()
{
	for (int i = 0; i < _pp; ++i)
	{
		RRMLib::DrawExtendGraph(_pos.x + i * OFFSET, _pos.y, _pos.x + IMG_W + i * OFFSET, _pos.y + IMG_H, _handle);
	}
}
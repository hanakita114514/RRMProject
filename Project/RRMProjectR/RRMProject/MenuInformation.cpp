#include "MenuInformation.h"
#include <RRMLib.h>
#include "common.h"

const float Y_ExtendLimit = 350;
const float X_ExtendLimit = 300;

MenuInformation::MenuInformation()
{
}


MenuInformation::~MenuInformation()
{

}

void 
MenuInformation::Init()
{
	_handle = RRMLib::LoadGraph("Resource/img/BackGround/whiteFilter.png");
	Rect r = {};
	_alpha = 0;

	_isReduction = false;
	_isEnlargement = false;
	_isWait = true;
	_extendX = _extendY = 0;
	_update = &MenuInformation::Wait;

	_extendPos[0] = Vector2(640, 350);
	_extendPos[1] = Vector2(640, 370);
}

void
MenuInformation::Update()
{
	(this->*_update)();
}

void
MenuInformation::Enlargement()
{
	_extendX += 40;

	if (_extendX > X_ExtendLimit)
	{
		_extendX = X_ExtendLimit;
		_extendY += 40;
	}
	if (_extendY > Y_ExtendLimit)
	{
		_extendY = Y_ExtendLimit;
		_update = &MenuInformation::Wait;
		_isWait = true;
	}
}

void
MenuInformation::Reduction()
{
	_extendY -= 50;
	if (_extendY <= 0)
	{
		_extendY = 0;
		_extendX -= 50;
	}

	if (_extendX <= 0)
	{
		_extendX = 0;
		_alpha = 0;
		_update = &MenuInformation::Wait;
		_isWait = true;
	}
}

void
MenuInformation::Wait()
{
	_isEnlargement = false;
	_isReduction = false;
}

void
MenuInformation::Enlargement(int extendRate, int alpha)
{
	_ExRate = extendRate;
	_isEnlargement = true;
	_isReduction = false;
	_alpha = alpha;

	_update = &MenuInformation::Enlargement;
}

void 
MenuInformation::Reduction(int extendRate)
{
	_ExRate = extendRate;
	_isEnlargement = false;
	_isReduction = true;

	_update = &MenuInformation::Reduction;
}

void
MenuInformation::Draw()
{
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, (int)_alpha);
	RRMLib::DrawExtendGraph(_extendPos[0].x - _extendX, _extendPos[0].y - _extendY,
							_extendPos[1].x + _extendX, _extendPos[1].y + _extendY,_handle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE,0);

}


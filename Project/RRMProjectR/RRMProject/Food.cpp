#include "Food.h"
#include <math.h>
#include "Block.h"
#include "Player.h"

static const float GRAVITY = 0.2f;

Food::Food() : _angle(0), _score(0), _deleteFlag(false), _collectFlag(false), _turnAngle(0), _friction(0.2f), _hitGround(false)
{
}


Food::~Food()
{
}

Food::FoodStatus
Food::GetFoodStatus()
{
	return _fs;
}

void 
Food::Collect(const Position& pos)
{
	_collectFlag = true;

	_vel = (pos - _rc.pos) / 10;
}


void 
Food::DistanceAttenuation()
{
	if (_vel.x > 0)
	{
		_vel.x -= _friction;
	}
	if (_vel.x < 0)
	{
		_vel.x += _friction;
	}
	if (fabsf(_vel.x) < 0.5f)
	{
		_vel.x = 0;
	}
}

void 
Food::Gravity()
{
	_vel.y += GRAVITY;

	if (_hitGround)
	{
		_vel.y = 0;
	}
}

void 
Food::ScreenLimit(Camera& camera)
{
	if (_rc.pos.x < camera.GetCameraRect().lpos.x)
	{
		_rc.pos.x = camera.GetCameraRect().lpos.x;
		_vel.x *= -1;
	}
	if (_rc.Right() > camera.GetCameraRect().rpos.x)
	{
		_rc.pos.x = camera.GetCameraRect().rpos.x - _rc.w;
		_vel.x *= -1;
	}
	if (_rc.Top() < camera.GetMapSize().pos.y)
	{
		_rc.pos.y = camera.GetMapSize().pos.y;
		_vel.y *= -1;
	}
	if (_rc.Top() > camera.GetMapSize().pos.y + camera.GetMapSize().h)
	{
		Destory();
	}
}

void
Food::Hit(Player* other)
{
	_deleteFlag = true;
}

void
Food::Hit(Block* other)
{
	float lenX = fabs(_rc.pos.x - other->GetRect().pos.x);
	float lenY = fabs(_rc.pos.y - other->GetRect().pos.y);

	if (lenX < lenY) // Yé≤Ç…âüÇµñﬂÇ∑
	{
		if (_vel.y > 0)		//óéâ∫ÇµÇƒÇ¢ÇÈèÍçá
		{
			if (_rc.pos.y < other->GetRect().pos.y && !_hitGround)
			{
				_rc.SetBottom(other->GetRect().Top());
				_hitGround = true;
				_vel.y = 0;
			}
		}
		else				//îÚÇÒÇ≈Ç¢ÇÈèÍçá
		{
			if (_rc.pos.y > other->GetRect().pos.y)
			{
				_rc.SetTop(other->GetRect().Bottom());
				_vel.y = 0;
			}
		}
	}

	if (lenY < lenX)	//Xé≤Ç…âüÇµñﬂÇ∑
	{
		if (_vel.x > 0)		//âEà⁄ìÆ
		{
			if (_rc.pos.x < other->GetRect().pos.x)
			{
				_rc.SetRight(other->GetRect().Left());
				_vel.x *= -1;
			}
		}
		else				//ç∂à⁄ìÆ
		{
			if (_rc.pos.x > other->GetRect().pos.x)
			{
				_rc.SetLeft(other->GetRect().Right());
				_vel.x *= -1;
			}
		}
	}
}
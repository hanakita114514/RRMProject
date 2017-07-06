#include "Jump.h"
#include "GameTime.h"

static const float jump_power = 20;
static const float fall_coefficient = 0.45f;


Jump::Jump(Input*& input, Vector2& vel, bool& hitGround, Object* owner) :
	_input(input), _vel(vel), _hitGround(hitGround), _owner(owner)
{
	_hitGround = false;
	_isAirJump = false;
	_isJump = false;
	_secondJump = true;
	_groundJump = true;

}


Jump::~Jump()
{
}

bool 
Jump::GroundJump()
{
	if (_vel.y > 0)
	{
		_isJump = false;
	}

	if (_input->Jump() && _hitGround && _groundJump)
	{
		_vel.y = -jump_power * GameTime::Instance().GetTimeScale(_owner);
		_isJump = true;
		_hitGround = false;
		_groundJump = false;
		return true;
	}
	return false;
}

bool 
Jump::AirJump()
{
	if (_secondJump && _input->Jump() && _isAirJump)
	{
		_vel.y = -jump_power * GameTime::Instance().GetTimeScale(_owner);
		_isJump = true;
		_secondJump = false;
		return true;
	}

	return false;
}

void 
Jump::Attenuation()
{
	if (_input->IsRelease(KeyType::keyY))
	{
		if (_isJump)
		{
			_vel.y *= fall_coefficient;
		}
		if (!_hitGround)
		{
			_isAirJump = true;
		}
	}
}

void 
Jump::HitGround()
{
	_isAirJump = false;
	_isJump = false;
	_secondJump = true;
	if (!_input->Jump())
	{
		_groundJump = true;
	}
}

void 
Jump::RevivalAirJump()
{
	_secondJump = true;
	_isAirJump = true;
}
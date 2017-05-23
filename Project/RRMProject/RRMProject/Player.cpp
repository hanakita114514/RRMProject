#include <DxLib.h>
#include "Player.h"
#include "BulletManeger.h"
#include "NormalBullet.h"
#include "GameMain.h"
#include"SinBullet.h"
#include "HomingBullet.h"
#include "Lazer.h"
#include "Block.h"

const float GRAVITY = 0.75f;

Player::Player(int padType) : _input(padType), _hp(100), _pp(3)
{
	_update = &Player::AliveUpdate;

	_handle = DxLib::LoadGraph("Resource/img/player/player.png");

	_handleMap[PlayerState::neutral] = DxLib::LoadGraph("Resource/img/player/player.png");
	_handleMap[PlayerState::attack] = DxLib::LoadGraph("Resource/img/player/attack.png");
	_handleMap[PlayerState::avoidance] = DxLib::LoadGraph("Resource/img/player/avoidance.png");


	Rect rc = {};
	_rc = rc;
	_rc.h = 64;
	_rc.w = 64;
	_dir = Vector2(1, 0);

	_hitGround = false;
	_isAirJump = false;
	_isJump = false;
	_secondJump = true;

	_speed = 6.0f;

	_ps = PlayerState::neutral;

	_state = &Player::Neutral;
	_isdir = &Player::DirRight;

	_grazePoint.radius = 11;
}


Player::~Player()
{
}

void
Player::Init()
{

}

void
Player::Move()
{
	if (_input.Left())
	{
		//_vel.x = std::fmaxf(-10.0f, _vel.x - 1);
		_vel.x = -_speed;
		_dir.x = -1;
		_isdir = &Player::DirLeft;
	}
	if (_input.Right())
	{
		//_vel.x = std::fminf(10.0f, _vel.x + 1);
		_vel.x = _speed;
		_dir.x = 1;
		_isdir = &Player::DirRight;
	}

}


void
Player::Jump()
{
	//地上ジャンプ
	if (_input.Jump() && _hitGround)
	{
		_vel.y = -20;
		_isJump = true;
		_hitGround = false;
	}

	if (_vel.y > 0)
	{
		_isJump = false;
	}

	if (_input.IsRelease(KeyType::keyY))
	{
		if (_isJump)
		{
			_vel.y *= 0.45f;
		}
		if (!_hitGround)
		{
			_isAirJump = true;
		}
	}

	if (_secondJump && _input.Jump() && _isAirJump)
	{
		_vel.y = -20;
		_isJump = true;
		_secondJump = false;
	}

}

void
Player::Attack()
{
	_ps = PlayerState::attack;

}

void
Player::Neutral()
{
	_ps = PlayerState::neutral;
}

void Player::Avoidance()
{
	_ps = PlayerState::avoidance;
}

void Player::Shoot()
{
	Vector2 end = Vector2(1280, 720);
	_ps = PlayerState::shoot;
		BulletManeger* bm = GameMain::Instance().GetBulletMng();
		Bullet* bullet = bm->GetFactory()->GetBullet(BulletType::normal, _dir, ObjectType::player, _shootPos);
		bullet->SetPos(_shootPos);
}

void
Player::AliveUpdate()
{
	_vel.x = 0;


	_grazePoint.pos.x = _rc.pos.x + _rc.w / 2;
	_grazePoint.pos.y = _rc.pos.y + _rc.h / 2;

	Move();
	Jump();


	(this->*_isdir)();
	
	if (_input.Attack())
	{

	}

	if (_input.Avoidance())
	{

	}

	if (_input.Shoot() || DxLib::CheckHitKey(KEY_INPUT_Z))
	{
		_state = &Player::Shoot;
	}
	else
	{
		_state = &Player::Neutral;
	}

	(this->*_state)();


	//仮の地面を作る
	if (_hitGround == true)
	{
		_vel.y = 0;

		_isAirJump = false;
		_isJump = false;
		_secondJump = true;
	}
	else
	{
		_vel.y += GRAVITY;
	}

	_rc.pos += _vel;
}

void 
Player::DyingUpdate()
{

}

void
Player::Update()
{
	_input.Update();

	(this->*_update)();

}

void
Player::Draw()
{

	switch (_ps)
	{
	case Player::PlayerState::none:
		break;
	case Player::PlayerState::neutral:
		DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handleMap[PlayerState::neutral], true);
		break;
	case Player::PlayerState::walk:
		break;
	case Player::PlayerState::attack:
	case Player::PlayerState::shoot:
		DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handleMap[PlayerState::attack], true);
		break;
	case Player::PlayerState::avoidance:
		DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handleMap[PlayerState::avoidance], true);

	default:
		break;
	}

	DxLib::DrawCircle(_grazePoint.pos.x, _grazePoint.pos.y, _grazePoint.radius, 0xff0000);
}

ObjectType 
Player::GetObjType()
{
	return ObjectType::player;
}

void
Player::DirRight()
{
	_shootPos = _rc.pos;
	_shootPos.x = _rc.Right();
}

void
Player::DirLeft()
{
	_shootPos = _rc.pos;
}

void Player::Hit(Enemy* other)
{

}

void Player::Hit(Block* other)
{
	if (_vel.x != 0 && _hitGround)
	{
		_vel.x < 0 ? _rc.SetLeft(other->GetRect().Right()) : _rc.SetRight(other->GetRect().Left());
	}
	if(_vel.y != 0)
	{
		_vel.y < 0 ? _rc.SetTop(other->GetRect().Bottom()) : _rc.SetBottom(other->GetRect().Top());
		if (_vel.y > 0) _hitGround = true;
		else _vel.y = 0;
	}
}

void Player::Hit(Bullet* other)
{

}

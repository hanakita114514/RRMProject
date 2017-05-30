#include <DxLib.h>
#include "Player.h"
#include "BulletManager.h"
#include "NormalBullet.h"
#include "GameMain.h"
#include"SinBullet.h"
#include "HomingBullet.h"
#include "Lazer.h"
#include "Block.h"
#include "GameTime.h"

const float GRAVITY = 0.75f;
const float jump_power = 20;
const float fall_coefficient = 0.45f;

Player::Player(int padType, Camera& camera) : _input(padType), _hp(100), _pp(3), _camera(camera)
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

	_state = &Player::NeutralState;
	_isdir = &Player::DirRight;

	_grazePoint.pos.x = _rc.w / 2;
	_grazePoint.pos.y = _rc.h / 2;
	_grazePoint.radius = 11;

	_avoidTime = 15.0f;
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
		_vel.x = -_speed * GameTime::Instance().GetTimeScale();
		_dir.x = -1;
		_isdir = &Player::DirLeft;
	}
	if (_input.Right())
	{
		//_vel.x = std::fminf(10.0f, _vel.x + 1);
		_vel.x = _speed * GameTime::Instance().GetTimeScale();
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
		_vel.y = -jump_power * GameTime::Instance().GetTimeScale();
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
			_vel.y *= fall_coefficient;
		}
		if (!_hitGround)
		{
			_isAirJump = true;
		}
	}

	if (_secondJump && _input.Jump() && _isAirJump)
	{
		_vel.y = -jump_power * GameTime::Instance().GetTimeScale();
		_isJump = true;
		_secondJump = false;
	}

}

void
Player::AttackState()
{
	_ps = PlayerState::attack;
}

void
Player::NeutralState()
{
	_ps = PlayerState::neutral;
}

void Player::AvoidanceUpdate()
{
	_avoidTime -= 1.0f * GameTime::Instance().GetTimeScale();

	_ps = PlayerState::avoidance;

	//発動した瞬間は動かない
	if (_avoidTime >= 10.0f)
	{
		return;
	}

	if (_avoidTime <= 0)
	{
		_update = &Player::AliveUpdate;
	}

	//その場回避
	if (_vel.x == 0 && _vel.y == 0)
	{
		return;
	}

	Vector2 v = Normalize(_vel);

	_rc.pos.x += v.x * 20.0f * GameTime::Instance().GetTimeScale();
	_rc.pos.y += v.y * 20.0f * GameTime::Instance().GetTimeScale();

	if (_hitGround == true)
	{
		_vel.y = 0;

		_isAirJump = false;
		_isJump = false;
		_secondJump = true;
	}
}

void Player::ShootState()
{
	Vector2 end = Vector2(1280, 720);
	_ps = PlayerState::shoot;
		Bullet* bullet = BulletManager::Instance().Create(BulletType::sinBullet, _dir, ObjectType::player, _shootPos, this);
		bullet->SetPos(_shootPos);
}

void
Player::AliveUpdate()
{
	_vel.x = 0;

	Move();
	Jump();
	(this->*_isdir)();
	
	if (_input.Attack())
	{

	}

	//回避
	if (_input.Avoidance())
	{
		if (_pp.GetPowerPoint() > 0)
		{
			_pp.Use();
			_vel = _input.Dir();
			_update = &Player::AvoidanceUpdate;
			_avoidTime = 15.0f;
			return;
		}

		//_sd.SlowMotion(60.0f);
	}

	//パリィ
	if (_input.Parry())
	{
		//_sd.TheWorld(30.0f);
		_camera.Quake(Vector2(0, 7));
	}

	//ショット
	if (_input.Shoot())
	{
		_state = &Player::ShootState;
	}

#ifdef DEBUG
	if (CheckHitKey(KEY_INPUT_Z)
	{
		_state = &Player::ShootState;
	}
#endif // DEBUG

	else
	{
		_state = &Player::NeutralState;
	}

	HitGround();

	(this->*_state)();



	// 止まってるときは動かさない
	if (GameTime::Instance().GetTimeScale() != 0)
	{
		_rc.pos.y += _vel.y;
	}

	_rc.pos.x += _vel.x;
}

void 
Player::DamageUpdate()
{

}

void 
Player::DyingUpdate()
{
	int a = 0;
}

void
Player::Update()
{
	_input.Update();
	_sd.Update();
	_pp.Update();

	(this->*_update)();

}

void
Player::Draw()
{
	Position drawPos;
	drawPos.x = _rc.pos.x + _camera.GetOffset().x;
	drawPos.y = _rc.pos.y + _camera.GetOffset().y;

	switch (_ps)
	{
	case Player::PlayerState::none:
		break;

	case Player::PlayerState::neutral:
		DxLib::DrawGraph(drawPos.x, drawPos.y, _handleMap[PlayerState::neutral], true);
		break;

	case Player::PlayerState::walk:
		break;

	case Player::PlayerState::attack:
		break;

	case Player::PlayerState::shoot:
		DxLib::DrawGraph(drawPos.x, drawPos.y, _handleMap[PlayerState::attack], true);
		break;

	case Player::PlayerState::avoidance:
		DxLib::DrawGraph(drawPos.x, drawPos.y, _handleMap[PlayerState::avoidance], true);
		break;

	default:
		break;
	}

	DxLib::DrawLine(_rc.Left() + (_rc.w / 2), _rc.Top(), _rc.Left() + (_rc.w / 2), _rc.Bottom(), 0xff0000, false);

#ifdef DEBUG
	_rc.DrawBox();

#endif // DEBUG

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
	_shootPos.x += _rc.w;
}

void
Player::DirLeft()
{
	_shootPos = _rc.pos;
}

void Player::Hit(Enemy* other)
{
	//if(!_mhp.IsAlreadyHit((Object*)other))
	//{
	//	_mhp.Hit((Object*)other);
	//}
}

void Player::Hit(Block* other)
{
	float lenX = fabs(_rc.pos.x - other->GetRect().pos.x);
	float lenY = fabs(_rc.pos.y - other->GetRect().pos.y);

	if (lenX < lenY) // Y軸に押し戻す
	{
		if (_vel.y > 0)		//落下している場合
		{
			if (_rc.pos.y < other->GetRect().pos.y && !_hitGround)
			{
				_rc.SetBottom(other->GetRect().Top());
				_hitGround = true;
				_vel.y = 0;
			}
		}
		else				//飛んでいる場合
		{
			if (_rc.pos.y > other->GetRect().pos.y)
			{
				_rc.SetTop(other->GetRect().Bottom());
				_vel.y = 0;
			}
		}
	}

	if (lenY < lenX)	//X軸に押し戻す
	{
		int i = 0;
		if (_dir.x == 1)		//右移動
		{
			if (_rc.pos.x < other->GetRect().pos.x)
			{
				_rc.SetRight(other->GetRect().Left());
				_vel.x = 0;
			}
		}
		else				//左移動
		{
			int i = 0;
			if (_rc.pos.x > other->GetRect().pos.x)
			{
				_rc.SetLeft(other->GetRect().Right());
				_vel.x = 0;
			}
		}
	}
}

void Player::Hit(Bullet* other)
{

}

void 
Player::SlowMotion()
{
	_sd.SlowMotion(60.0f);
}

void
Player::HitGround()
{
	if (_hitGround == true)
	{
		_vel.y = 0;

		_isAirJump = false;
		_isJump = false;
		_secondJump = true;
	}
	else
	{
		_vel.y += GRAVITY * GameTime::Instance().GetTimeScale() * GameTime::Instance().GetTimeScale();
	}
}
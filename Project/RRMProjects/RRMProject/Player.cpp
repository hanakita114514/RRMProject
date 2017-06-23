#include <RRMLib.h>
#include "Player.h"
#include "BulletManager.h"
#include "NormalBullet.h"
#include "GameMain.h"
#include "SinBullet.h"
#include "HomingBullet.h"
#include "Lazer.h"
#include "Block.h"
#include "GameTime.h"
#include "Enemy.h"
#include "EffectManager.h"

const float GRAVITY = 0.75f;
const float jump_power = 20;
const float fall_coefficient = 0.45f;
const int slow_second = 60;					//時間が遅くなる秒数
const int stop_second = 30;					//時間を止める秒数

const int armor_life = 200.0f;				//アーマーの耐久値


Player::Player(int padType, Camera& camera) 
	: _input(padType), _hp(100), _pp(3), _camera(camera) , _armor(armor_life)
{
	_update = &Player::AliveUpdate;

	_handle = RRMLib::LoadGraph("Resource/img/player/player.png");

	_handleMap[PlayerState::neutral] = RRMLib::LoadGraph("Resource/img/player/player.png");
	_handleMap[PlayerState::attack] = RRMLib::LoadGraph("Resource/img/player/attack.png");
	_handleMap[PlayerState::avoidance] = RRMLib::LoadGraph("Resource/img/player/avoidance.png");


	Rect rc = {};
	_rc = rc;
	_rc.h = 64;
	_rc.w = 64;
	_dir = Vector2(1, 0);

	_hitGround = false;
	_isAirJump = false;
	_isJump = false;
	_secondJump = true;
	_nosedive = 1;

	_speed = 6.0f;
	_ps = PlayerState::neutral;
	_isdir = &Player::DirRight;

	_tool[0] = BulletType::normal;
	_tool[1] = BulletType::deffusion;
	_tool[2] = BulletType::homing;
	_toolIdx = 0;

	_avoidTime = 15.0f;

	_armor = armor_life;

	_attackTime = 0;

	_attack = &Player::FirstAttack;
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
		_vel.x = -_speed * GameTime::Instance().GetTimeScale(this);
		_dir.x = -1;
		_isdir = &Player::DirLeft;
	}
	if (_input.Right())
	{
		//_vel.x = std::fminf(10.0f, _vel.x + 1);
		_vel.x = _speed * GameTime::Instance().GetTimeScale(this);
		_dir.x = 1;
		_isdir = &Player::DirRight;
	}
	if (_input.Nosedive())
	{
		_nosedive = 3;
	}
}


void
Player::Jump()
{
	//地上ジャンプ
	if (_input.Jump() && _hitGround)
	{
		_vel.y = -jump_power * GameTime::Instance().GetTimeScale(this);
		_isJump = true;
		_hitGround = false;
		_nosedive = 1;
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
		_vel.y = -jump_power * GameTime::Instance().GetTimeScale(this);
		_isJump = true;
		_secondJump = false;
		_nosedive = 1;
	}
}

void 
Player::InvincibleUpdate()
{
	_invincibleTime -= 1 * GameTime::Instance().GetTimeScale(this);
	_ps = PlayerState::invincible;

	_vel.x = 0;

	Move();
	Jump();

	HitGround();


	// 時間が止まってるときは動かさない
	if (GameTime::Instance().GetTimeScale(this) != 0)
	{
		_rc.pos.y += _vel.y;
	}

	_rc.pos.x += _vel.x;

	if (_invincibleTime <= 0)
	{
		_update = &Player::AliveUpdate;
	}
}

void Player::AvoidanceUpdate()
{
	_avoidTime -= 1.0f * GameTime::Instance().GetTimeScale(this);

	_nosedive = 1;

	_ps = PlayerState::avoidance;

	//発動した瞬間は動かない
	if (_avoidTime >= 11.0f)
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

	_rc.pos.x += v.x * 23.0f * GameTime::Instance().GetTimeScale(this);
	_rc.pos.y += v.y * 23.0f * GameTime::Instance().GetTimeScale(this);

	if (_hitGround == true)
	{
		_vel.y = 0;

		_isAirJump = false;
		_isJump = false;
		_secondJump = true;
	}
}

void Player::Shoot()
{
	Vector2 end = Vector2(1280, 720);
	_ps = PlayerState::shoot;
		Bullet* bullet = BulletManager::Instance().Create(_tool[_toolIdx], _dir, ObjectType::player, _shootPos, this);
		bullet->SetPos(_shootPos);
}

void 
Player::FirstAttack()
{
	_hitBox.FirstAttack(_attackTime, _rc, _dir);

	--_attackTime;

	if (_attackTime <= 0)
	{
		_update = &Player::AliveUpdate;
		_hitBox.Clear();
	}
}
void 
Player::SecondAttack()
{

}
void 
Player::UpAttack()
{

}

void 
Player::DonwAttack()
{

}

void
Player::AttackUpdate()
{
	(this->*_attack)();
}

void
Player::AliveUpdate()
{
	_ps = PlayerState::neutral;

	_vel.x = 0;

	Move();
	Jump();
	(this->*_isdir)();
	
	if (_input.Attack())
	{
		_update = &Player::AttackUpdate;
		_attack = &Player::FirstAttack;
		_attackTime = 10.f;
		return;
	}

	//回避
	if (_input.Avoidance())
	{
		if (_pp.GetPowerPoint() > 0)
		{
			_pp.Use();
			_vel = _input.Dir();
			_update = &Player::AvoidanceUpdate;
			_avoidTime = 17.0f;
			_nosedive = 1;
			_secondJump = true;
			_isAirJump = true;
			EffectManager::Instance().Create(EffectType::erasure, _rc.Center(), Vector2(1.0f, 1.0f), 0.7f, false);
			return;
		}

		//_sd.SlowMotion(60.0f);
	}

	//パリィ
	if (_input.Parry())
	{
		_sd.TheWorld(stop_second);
		_camera.Quake(Vector2(0, 7));
	}

	//ショット
	if (_input.Shoot())
	{
		Shoot();
	}

	//消化
	if (_input.Digestion())
	{
		_dig.Digest();
	}

	//飛び道具切り替え
	ToolSwitch();

#ifdef DEBUG
	//if (CheckHitKey(KEY_INPUT_Z)
	//{
	//	_state = &Player::ShootState;
	//}
#endif // DEBUG

	HitGround();

	// 時間が止まってるときは動かさない
	if (GameTime::Instance().GetTimeScale(this) != 0)
	{
		_rc.pos.y += _vel.y;
	}

	_rc.pos.x += _vel.x;

}

void 
Player::DamageUpdate()
{
	_ps = PlayerState::damage;
		_vel.y += GRAVITY * GameTime::Instance().GetTimeScale(this) * GameTime::Instance().GetTimeScale(this);
	// 時間が止まってるときは動かさない
	if (GameTime::Instance().GetTimeScale(this) != 0)
	{
		_rc.pos.y += _vel.y;
		_rc.pos.x += _vel.x;
	}


	DistanceAttenuation();
	if (_vel.x == 0)
	{
		_update = &Player::InvincibleUpdate;
		_invincibleTime = 60.0f;
	}
}

void 
Player::DyingUpdate()
{
}

void
Player::Update()
{
	_input.Update();

	if (!_hitStop.IsHitStop())
	{
		_sd.Update();
		_pp.Update();
		_armor.AutomaticRecovery();

		(this->*_update)();
	}
	_hitStop.Update();


	//移動制限
	if (_camera.GetMapSize().w <= _rc.pos.x + _rc.w)
	{
		_rc.pos.x = _camera.GetMapSize().w - _rc.w;
		_vel.x = 0;
	}
	if (_rc.pos.x <= 0)
	{
		_rc.pos.x = 0;
		_vel.x = 0;
	}

	if (_camera.GetMapSize().h <= _rc.pos.y)
	{
		_rc.pos.y = _camera.GetMapSize().h;
	}
	if (_rc.pos.y <= 0 - 128)
	{
		_rc.pos.y = 0 - 128;
	}

}

void
Player::Draw()
{
	Position drawPos;
	drawPos.x = _rc.pos.x - _camera.GetOffset().x;
	drawPos.y = _rc.pos.y - _camera.GetOffset().y;

	switch (_ps)
	{
	case Player::PlayerState::none:
		break;

	case Player::PlayerState::neutral:
		RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handleMap[PlayerState::neutral]);
		break;

	case Player::PlayerState::walk:
		break;

	case Player::PlayerState::attack:
		break;

	case Player::PlayerState::shoot:
		RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handleMap[PlayerState::attack]);
		break;

	case Player::PlayerState::avoidance:
		RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handleMap[PlayerState::avoidance]);
		break;

	case Player::PlayerState::invincible:
		if (((int)_invincibleTime / 3) % 2 == 0)
		{
			RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handleMap[PlayerState::neutral]);
		}
		break;
	case Player::PlayerState::damage:
		RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handleMap[PlayerState::neutral]);
		break;
	default:
		break;
	}

	RRMLib::DrawLine((int)(_rc.Left() + (_rc.w / 2)), (int)(_rc.Top()),
					(int)(_rc.Left() + (_rc.w / 2)), (int)(_rc.Bottom()), 0xff0000);
	_hitBox.Draw();

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

	float lenX = fabs(_rc.pos.x - other->GetRect().pos.x);
	float lenY = fabs(_rc.pos.y - other->GetRect().pos.y);

	if (_ps != PlayerState::avoidance) // 回避中ではなかったら処理をする
	{
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
				if (_rc.pos.x > other->GetRect().pos.x)
				{
					_rc.SetLeft(other->GetRect().Right());
					_vel.x = 0;
				}
			}
		}
	}
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
	if (other->GetObjType() == ObjectType::enemy)
	{
		if (_update == &Player::AliveUpdate)
		{
			Damage(other->GetPower());
			return;
		}
		if (_update == &Player::AvoidanceUpdate)
		{
			_sd.SlowMotion(5, this);
			_sd.SlowMotion(60, other->GetOwner());
			return;
		}
	}
}

void 
Player::SlowMotion()
{
	_sd.SlowMotion(slow_second);
}

void
Player::HitGround()
{
	if (_hitGround)
	{
		_vel.y = 0;

		_isAirJump = false;
		_isJump = false;
		_secondJump = true;
		_nosedive = 1;
	}
	else
	{
		_vel.y += GRAVITY * GameTime::Instance().GetTimeScale(this) * GameTime::Instance().GetTimeScale(this) * _nosedive;
	}
}

void
Player::ToolSwitch()
{
	if (_input.ToolSwitch())
	{
		_toolIdx++;
		_toolIdx = (_toolIdx + 1) % ToolMax;
	}
}

void
Player::WeaponSwitch()
{
	if (_input.WeaponSwitch())
	{

	}
}

bool 
Player::IsAvoidance()
{
	return _update == &Player::AvoidanceUpdate;
}

bool 
Player::IsDamage()
{
	if (_update == &Player::DamageUpdate)
	{
		return true;
	}
	return false;
}

void 
Player::DistanceAttenuation()
{
	if (_vel.x > 0)
	{
		_vel.x -= 0.2f;
	}
	if (_vel.x < 0)
	{
		_vel.x += 0.2f;
	}
	if (abs(_vel.x) < 0.5f)
	{
		_vel.x = 0;
	}
}

void
Player::Damage(float power)
{
	_armor.Damage(power);
	_hp.Damage(power);
	if (_armor.IsBroken())
	{
		_armor.Recovery();
		_vel.x = _dir.x * 10.0f * -1.0f;
		_vel.y = -8.0f;
		_update = &Player::DamageUpdate;
	}
}
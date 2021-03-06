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
#include "InputFactory.h"
#include "GraphicLoad.h"
#include "SoundManager.h"
#include "Food.h"

static const float jump_power = 20;
static const float GRAVITY = 0.75f;
static const float fall_coefficient = 0.45f;
static const int slow_second = 60;					//時間が遅くなる秒数
static const int stop_second = 30;					//時間を止める秒数

static const int armor_life = 200.0f;				//アーマーの耐久値


Player::Player(int padType, Camera& camera, InputMode mode) 
	: _hp(1000), _pp(4), _camera(camera) , _armor(armor_life),
	_jump(_input, _vel, _hitGround, this), _playerDraw(_rc, _dir)
{

	Player::LoadResources();

	Player::MapInit();

	Rect rc = {};
	_rc = rc;
	_rc.h = 128;
	_rc.w = 96;
	_dir = Vector2(1, 0);

	_hitGround = false;

	_nosedive = 1;

	_speed = 6.0f;
	_ps = PlayerState::neutral;

	_tool[0] = BulletType::normal;
	_tool[1] = BulletType::homing;
	_tool[2] = BulletType::dropBullet;
	_toolIdx = 0;

	_avoidTime = 15.0f;

	_armor = armor_life;

	_attackTime = 0;

	_turnFlag = false;

	_animFrame = 0;

	_addAttackFlag = false;
	_airAttackFlag = true;

	_input = InputFactory::Create(mode, padType);

	_weapon = Weapon::gladius;
}


Player::~Player()
{
}

void 
Player::LoadResources()
{
	//_handle = RRMLib::LoadGraph("Resource/img/player/player.png");

	//_handleMap[PlayerState::neutral] = RRMLib::LoadGraph("Resource/img/player/Healer/$Healer_1.png");
	//_handleMap[PlayerState::neutral] = RRMLib::LoadGraph("Resource/img/player/player.png");
	//_handleMap[PlayerState::attack] = RRMLib::LoadGraph("Resource/img/player/attack.png");
	//_handleMap[PlayerState::avoidance] = RRMLib::LoadGraph("Resource/img/player/Healer/$Healer_4.png");
	//_handleMap[PlayerState::avoidance] = RRMLib::LoadGraph("Resource/img/player/avoidance.png");

	_weaponHandle[Weapon::gladius] = GraphicLoad::Instance().LoadGraph("Resource/img/player/weapon/gladius2.png");
	_weaponHandle[Weapon::gladiusU] = GraphicLoad::Instance().LoadGraph("Resource/img/player/weapon/gladius2u.png");
	_weaponHandle[Weapon::gladiusD] = GraphicLoad::Instance().LoadGraph("Resource/img/player/weapon/gladius2d.png");
}

void 
Player::MapInit()
{
	//Update関数をマップに格納
	_update[UpdateState::attack] = &Player::AttackUpdate;
	_update[UpdateState::avoidance] = &Player::AvoidanceUpdate;
	_update[UpdateState::damage] = &Player::DamageUpdate;
	_update[UpdateState::invincible] = &Player::InvincibleUpdate;
	_update[UpdateState::alive] = &Player::AliveUpdate;
	_update[UpdateState::dying] = &Player::DyingUpdate;

	//攻撃ステート関数をマップに格納
	_attack[AttackState::first] = &Player::FirstAttack;
	_attack[AttackState::second] = &Player::SecondAttack;
	_attack[AttackState::third] = &Player::ThirdAttack;
	_attack[AttackState::up] = &Player::UpAttack;
	_attack[AttackState::down] = &Player::DownAttack;
	_attack[AttackState::air] = &Player::AirAttack;

	_us = UpdateState::alive;
	_as = AttackState::first;
}

void
Player::Init()
{
	_hp.FullRecovery();
	_rc.pos = Vector2(0, 0);
}

void
Player::Move()
{
	if (_input->Left())
	{
		//_vel.x = std::fmaxf(-10.0f, _vel.x - 1);
		_vel.x = -_speed * GameTime::Instance().GetTimeScale(this);
		_dir.x = -1;

		if (_ps != PlayerState::invincible)
		{
			_ps = PlayerState::walk;
		}
	}
	if (_input->Right())
	{
		//_vel.x = std::fminf(10.0f, _vel.x + 1);
		_vel.x = _speed * GameTime::Instance().GetTimeScale(this);
		_dir.x = 1;

		if (_ps != PlayerState::invincible)
		{
			_ps = PlayerState::walk;
		}
	}
	if (_input->Nosedive())
	{
		_nosedive = 3;
	}
}


void
Player::Jump()
{
	if (_jump.GroundJump())
	{
		_nosedive = 1;
	}

	_jump.Attenuation();

	if(_jump.AirJump())
	{
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
		_us = UpdateState::alive;
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
		_us = UpdateState::alive;
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

		_jump.HitGround();
	}
}

void Player::Shoot()
{
	//右向き
	if (_dir.x > 0)
	{
		DirRight();
	}
	else
	{
		DirLeft();
	}


	if (_toolIdx == 2)
	{
		_dir.y = -1;
	}
	else
	{
		_dir.y = 0;
	}

	Vector2 end = Vector2(1280, 720);
	BulletManager::Instance().Create(_tool[_toolIdx], _shootPos, _dir, ObjectType::player, _shootPos, this);

}

void 
Player::FirstAttack()
{
	_hitBox.FirstAttack(_attackTime, _rc, _dir);

	--_attackTime;

	if (_input->Attack())
	{
		_addAttackFlag = true;
	}

	if (Avoidance())
	{
		_as = AttackState::first;
		_addAttackFlag = false;
	}

	if (_attackTime <= 0)
	{
		if (_addAttackFlag)
		{
			_as = AttackState::second;
			_attackTime = 15;
		}
		else
		{
			_us = UpdateState::alive;
		}
		_hitBox.Clear();
		_mhp.Clear();
		_addAttackFlag = false;
	}
}

void 
Player::SecondAttack()
{

	_hitBox.SecondAttack(_attackTime, _rc, _dir);

	--_attackTime;

	if (_input->Attack())
	{
		_addAttackFlag = true;
	}
	
	if (Avoidance())
	{
		_as = AttackState::first;
		_addAttackFlag = false;
	}

	if (_attackTime <= 0)
	{
		if (_addAttackFlag)
		{
			_as = AttackState::third;
			_attackTime = 30;
		}
		else
		{
			_us = UpdateState::alive;
		}
		_hitBox.Clear();
		_mhp.Clear();
		_addAttackFlag = false;
	}

}

void 
Player::ThirdAttack()
{
	_hitBox.ThirdAttack(_attackTime, _rc, _dir);

	--_attackTime;

	if (Avoidance())
	{
		_as = AttackState::first;
		_addAttackFlag = false;
	}

	if (_attackTime <= 0)
	{
		_us = UpdateState::alive;
		_hitBox.Clear();
		_mhp.Clear();
		_addAttackFlag = false;
	}
}

void 
Player::UpAttack()
{
	static const int duration = 10;

	_hitBox.UpAttack(_attackTime, _rc, _dir);

	_rc.pos += _vel;

	HitGround();

	++_attackTime;


	if (_attackTime >= duration)
	{
		_us = UpdateState::alive;
		_hitBox.Clear();
		_mhp.Clear();
		_addAttackFlag = false;
	}
}

void 
Player::DownAttack()
{
	static const int duration = 10;

	_hitBox.DownAttack(_attackTime, _rc, _dir);

	++_attackTime;
	_rc.pos += _vel;

	if (_attackTime >= duration)
	{
		_us = UpdateState::alive;
		_hitBox.Clear();
		_mhp.Clear();
		_addAttackFlag = false;
	}
}

void 
Player::AirAttack()
{
	static const int duration = 10;

	_hitBox.AirAttack(_attackTime, _rc, _dir);

	++_attackTime;

	if (_attackTime >= duration)
	{
		_us = UpdateState::alive;
		_hitBox.Clear();
		_mhp.Clear();
		_addAttackFlag = false;
	}
}

void
Player::AttackUpdate()
{
	(this->*_attack[_as])();
	_ps = PlayerState::attack;
}

void
Player::AliveUpdate()
{
	_ps = PlayerState::neutral;

	_vel.x = 0;

	Move();
	Jump();

	_hitBox.Clear();
	_hpbar.CommitPeriod();
	_hitBox.DamageBox(0, _rc, _dir);

	if (_input->UpAttack())
	{
		_us = UpdateState::attack;
		_as = AttackState::up;
		_weapon = Weapon::gladiusU;
		_attackTime = 0.f;
		return;
	}

	if (_input->DownAttack())
	{
		_us = UpdateState::attack;
		_as = AttackState::down;
		_weapon = Weapon::gladiusU;
		_attackTime = 0.f;
		return;
	}
	
	if (_input->Attack())
	{
		if ((_vel.y > 1 || _vel.y < -1))
		{
			if (_airAttackFlag)
			{
				_us = UpdateState::attack;
				_as = AttackState::air;
				_attackTime = 0.f;
				_weapon = Weapon::gladiusD;
				_airAttackFlag = false;
			}

			return;
		}
		_us = UpdateState::attack;
		_as = AttackState::first;
		_attackTime = 10.f;
		_weapon = Weapon::gladius;
		return;
	}

	//回避
	if (Avoidance())
	{
		return;
	}

	//パリィ
	if (_input->Parry())
	{
		_sd.TheWorld(stop_second);
		_camera.Quake(Vector2(0, 7));
	}

	//ショット
	if (_input->Shoot(30))
	{
		SoundManager::Instance().PlayFromStart(SEType::shot);
		Shoot();
	}

	//消化
	if (_input->Digestion())
	{
		_dig.Digest();
	}

	//飛び道具切り替え
	ToolSwitch();

	WeaponSwitch();


	if (_vel.y > 1 || _vel.y < -1)
	{
		_ps = PlayerState::jump;
	}

#ifdef DEBUG

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

	_hitBox.DamageBox(0, _rc, _dir);


	DistanceAttenuation();
	if (_vel.x == 0)
	{
		_us = UpdateState::invincible;
		_invincibleTime = 60.0f;
		_hpbar.Commit();
	}
}

void 
Player::DyingUpdate()
{
}

void
Player::Update()
{
	_input->Update();

	if (!_hitStop.IsHitStop())
	{
		_pp.Update();
		_armor.AutomaticRecovery();

		(this->*_update[_us])();
	}
	if (_ps == PlayerState::attack)
	{
		if (_input->Attack())
		{
			_addAttackFlag = true;
		}
	}
	_hpbar.Update();
	_hitStop.Update();
	_combo.Update();


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

	_animFrame++;
}

void 
Player::SlowDownUpdate()
{
	_sd.Update();
}

void
Player::Draw()
{
	Position drawPos;
	drawPos.x = _rc.pos.x - _camera.GetOffset().x;
	drawPos.y = _rc.pos.y - _camera.GetOffset().y;

	_playerDraw.Draw(drawPos, _ps);

	//RRMLib::DrawLine((int)(_rc.Left() + (_rc.w / 2)), (int)(_rc.Top()),
	//				(int)(_rc.Left() + (_rc.w / 2)), (int)(_rc.Bottom()), 0xff0000);

	_hitBox.Draw(_weaponHandle[_weapon]);

#ifdef DEBUG
	_rc.DrawBox();

#endif // DEBUG
}

void
Player::UIDraw()
{
	_hpbar.Draw(_hp);
	_pp.Draw();
	_combo.Draw();
}

ObjectType 
Player::GetObjType()
{
	return ObjectType::player;
}

void
Player::DirRight()
{
	_shootPos = _rc.Center();
	_shootPos.x += _rc.w / 2;
	_turnFlag = true;
}

void
Player::DirLeft()
{
	_turnFlag = false;
	_shootPos = _rc.Center();
	_shootPos.x -= _rc.w / 2;
}

void Player::Hit(Enemy* other)
{

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
		if(_us == UpdateState::alive)
		{
			Damage(other->GetPower());
			other->Finalize();
			return;
		}
		if(_us == UpdateState::avoidance)
		{
			_sd.SlowMotion(5, this);
			_sd.SlowMotion(60, other->GetOwner());
			return;
		}
	}
}

void
Player::Hit(Food* other)
{
}

void 
Player::SlowMotion()
{
	_sd.SlowMotion(5, this);
}

void
Player::SlowMotion(Object* other)
{
	_sd.SlowMotion(slow_second, other);
}

void
Player::HitGround()
{
	if (_hitGround)
	{
		_vel.y = 0;
		_nosedive = 1;

		_jump.HitGround();
		_airAttackFlag = true;
	}
	else
	{
		_vel.y += GRAVITY * GameTime::Instance().GetTimeScale(this) * GameTime::Instance().GetTimeScale(this) * _nosedive;
	}
}

void
Player::ToolSwitch()
{
	if (_input->ToolSwitch())
	{
		_toolIdx++;
		_toolIdx = (_toolIdx + 1) % ToolMax;
	}
}

void
Player::WeaponSwitch()
{
	if (_input->WeaponSwitch())
	{
	}
}

bool 
Player::IsAvoidance()
{
	//return _update == &Player::AvoidanceUpdate;
	return _us == UpdateState::avoidance;
}

bool 
Player::IsDamage()
{
	//return _update == &Player::DamageUpdate;
	return _us == UpdateState::damage;
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
		_combo.Failure();
		_armor.Recovery();
		_vel.x = _dir.x * 10.0f * -1.0f;
		_vel.y = -8.0f;
		_us = UpdateState::damage;
		_hitBox.Clear();
	}
}

void 
Player::Damage(float power, HitBox hitBox)
{
	_armor.Damage(power);
	_hp.Damage(power);
	_combo.Failure();

	_vel = hitBox.vec;
	_us = UpdateState::damage;
	_hitBox.Clear();
}

bool
Player::IsDead()
{
	return _hp.IsDead();
}

bool 
Player::Avoidance()
{
	if (_input->Avoidance())
	{
		if (!_pp.IsAbsentPP())
		{
			_pp.Use();
			_vel = _input->Dir();
			_us = UpdateState::avoidance;

			_avoidTime = 17.0f;
			_nosedive = 1;

			_jump.RevivalAirJump();

			SoundManager::Instance().PlayFromStart(SEType::avoid);
			EffectManager::Instance().Create(EffectType::erasure, _rc.Center(), Vector2(1.0f, 1.0f), 0.7f, false);
			return true;
		}
	}

	return false;
}
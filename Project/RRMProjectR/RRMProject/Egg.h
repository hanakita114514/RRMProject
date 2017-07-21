#pragma once
#include "Enemy.h"
#include "Circle.h"
#include "BulletManager.h"

const float ANIM_SPEED = 0.5;

enum ShootDir
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};

enum class EggState : unsigned int
{
	wait,
	shot,
	jump,
	coolTime,
	max
};

class Egg : public Enemy
{
private:
	int _shotCnt;				//���˃J�E���g
	float _animCnt;				//�A�j���[�V�����J�E���g
	Vector2 _uv;
	Vector2 _shotPos;
	Circle _circle;
	Vector2 _shootVec;
	int _freamCnt;
	float _searchTime;
	void Jump();

	Rect _territory;

	void (Egg::*_update)();

	void AliveUpdate();
	void DyingUpdate();
	void DamageUpdate();

	void Anim();

	EggState _state;

	using EggState = void (Egg::*)();

	EggState _stateUpdate[(int)EggState::max];
public:
	Egg(int handle, const Position& pos);
	~Egg();

	void Initialize();								//������
	void Update();									//�X�V
	void Draw(const Vector2& offset);				//�`��
	void Move();

	void Shot();

	void Wait();

	void CoolTime();

	void Shot(BulletType type,int count = 0);		//�U��

	//��̉�
	void Weakening();
};



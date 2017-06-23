#pragma once
#include "Enemy.h"
#include "Circle.h"
#include "BulletManager.h"
#include "HPBar.h"

const float ANIM_SPEED = 0.5;

enum ShootDir
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};

class Egg : public Enemy
{
private:
	int _shotCnt;				//���˃J�E���g
	float _animCnt;				//�A�j���[�V�����J�E���g
	Vector2 _uv;
	int suffix;
	int _junpCnt;
	Vector2 _shootPos[ShootDir::MAX];
	Vector2 _shotPos;
	Circle _circle;
	Vector2 _shootVec;
	bool ret;
	int _freamCnt;

	HPBar _hpbar;

	void Jump();

	void (Egg::*_update)();

	void AliveUpdate();
	void DyingUpdate();

public:
	Egg(int handle, const Position& pos);
	~Egg();

	void Initialize();								//������
	void Update();									//�X�V
	void Draw(const Vector2& offset);				//�`��
	void Anim();
	void Move();

	void Shot();

	void Wait();

	void(Egg::*_state)();

	void Shot(BulletType type,int count = 0);		//�U��

	void ShotAngleCalc(Vector2 shootPos);

	//��̉�
	void Weakening();

};


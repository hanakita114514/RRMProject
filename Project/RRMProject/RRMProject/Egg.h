#pragma once
#include "Enemy.h"
const int IMAGE_NUM = 3;
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
	int _img[IMAGE_NUM];		//�摜�n���h��
	int _animCnt;				//�A�j���[�V�����J�E���g
	int suffix;
	int _junpCnt;
	Vector2 _shootPos[ShootDir::MAX];
	Circle _circle;
	Vector2 _shootVec;
	bool ret;
	int _freamCnt;

	void Jump();
public:
	Egg(int* handle);
	~Egg();

	void Initialize();			//������
	void Update();				//�X�V
	void Draw();				//�`��
	void Anim();
	void Move();

	void Shot();

	void Wait();

	void(Egg::*_state)();

	void Shot(BulletType type,int count = 0);	//�U��

	void ShotAngleCalc(Vector2 shootPos);

	virtual void Hit(Player* other);
	virtual void Hit(Block* other);

};


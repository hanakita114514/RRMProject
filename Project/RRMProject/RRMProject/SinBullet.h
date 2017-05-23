#pragma once
#include "Bullet.h"

class SinBullet : public Bullet
{
private:

	int _freamCnt;
public:
	SinBullet(int handle);
	~SinBullet();

	virtual void Initialize(Vector2 vec,ObjectType type);				//������
	void Update();					//�X�V
	void Draw();					//�`��

	void Move();					//�ړ�
	void LifeDecree();				//���C�t�̌��Z
};


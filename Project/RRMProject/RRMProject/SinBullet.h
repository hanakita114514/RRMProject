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
	void Draw(const Vector2& offset);					//�`��

	void Move();					//�ړ�
	void LifeDecrease();				//���C�t�̌��Z
};


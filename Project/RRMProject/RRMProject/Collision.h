#pragma once
#include "Vector2.h"
class Rect;
class Circle;
class Player;
class Enemy;

//������Ώۂ��ǂ̕����ɓ����Ă��邩������
enum MOVE_CHECK
{
	up,
	right,
	down,
	left,
	none
};

class Collision
{
private:
	MOVE_CHECK _move;

	Vector2 sink;					//�߂荞�񂾗�

public:
	Collision();
	~Collision();

	bool IsHit(Rect &a, Vector2 velA,Rect &b);		//��`���m�̂����蔻��
	bool IsHit(Rect &r, Circle &c);			//��`�Ɖ~
	bool IsHit(Circle &c1, Circle &c2);
	bool LineCross(Rect r1, Vector2 vec1, Rect r2);	//��������(��`�Ƌ�`)

	void PushBack(Rect r,Player &p);
	void PushBack(Rect r, Enemy &e);

	//ra�̓v���C���[��G�Arb�ɂ͓����Ȃ����́i�u���b�N���j���w��A�x�N�g���̓v���C���[���G�̂���
	void PushBack(Rect &ra, Rect &rb,Vector2 vecA);
};


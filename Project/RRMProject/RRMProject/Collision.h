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

public:
	Collision();
	~Collision();

	bool IsHit(Rect &a,Rect &b);		//��`���m�̂����蔻��
	bool IsHit(Rect &r, Circle &c);			//��`�Ɖ~
	bool IsHit(Circle &c1, Circle &c2);

	bool LineCross(Rect r1, Vector2 vec1, Rect r2,bool hitGround);	//��������(��`�Ƌ�`)

	bool LineCross(Rect rA,Vector2 vecA, Rect rB,Vector2 vecB); //���������i�x�N�g�����m�j


};


#pragma once
#include "Vector2.h"
class Rect;
class Circle;
class Player;
class Enemy;

//あたる対象がどの方向に動いているかを示す
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

	Vector2 sink;					//めり込んだ量

public:
	Collision();
	~Collision();

	bool IsHit(Rect &a, Vector2 velA,Rect &b);		//矩形同士のあたり判定
	bool IsHit(Rect &r, Circle &c);			//矩形と円
	bool IsHit(Circle &c1, Circle &c2);
	bool LineCross(Rect r1, Vector2 vec1, Rect r2);	//線分交差(矩形と矩形)

	void PushBack(Rect r,Player &p);
	void PushBack(Rect r, Enemy &e);

	//raはプレイヤーや敵、rbには動かないもの（ブロック等）を指定、ベクトルはプレイヤーか敵のもの
	void PushBack(Rect &ra, Rect &rb,Vector2 vecA);
};


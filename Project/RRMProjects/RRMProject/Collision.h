#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Circle.h"
class Player;
class Enemy;
class Block;

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

public:
	Collision();
	~Collision();

	bool IsHit(Rect &a,Rect &b);		//矩形同士のあたり判定
	bool IsHit(Rect &r, Circle &c);			//矩形と円
	bool IsHit(Circle &c1, Circle &c2);
	bool IsHit(Rect &player, Block &block,Vector2 vec);

	//bool LineCross(Rect r1, Vector2 vec1, Rect r2,bool hitGround);	//線分交差(矩形と矩形)

	bool LineCross(Rect character,Vector2 characterVec, Vector2 posB,Vector2 vecB); //円と矩形の線分交差（ベクトル同士）

	bool LineCross(Rect characterA, Vector2 vecA, Rect characterB, Vector2 vecB);   //矩形と矩形の線分交差（ベクトル）


	bool LinerInterpolation(Rect& rect, Vector2& velocityA, Circle& circle, Vector2& velocityB);//線形補間(円と矩形)

};


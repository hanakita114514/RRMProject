#include "Collision.h"
#include "RectObj.h"
#include "CircleObj.h"
#include "Player.h"
#include <math.h> 
#include "Enemy.h"
#include "Block.h"
Collision::Collision()
{
	_move = none;
}


Collision::~Collision()
{
}
//円が矩形に当たっているかどうか
bool CircleColToRect(Rect &a, Circle &c); 

//2点間の距離を求める
float DistanceCalcuration(Vector2 &v1, Vector2 &v2);

bool Collision::IsHit(Rect &a, Rect &b)
{

	//if ((a.Right() < b.Left()) ||
	//	(a.Left() > b.Right()) ||
	//	(a.Bottom() < b.Top()) ||
	//	(a.Top() > b.Bottom()))
	//{
	//	return false;
	//}

	if ((a.Right() > b.Left()) &&
		(a.Left() < b.Right()) &&
		(a.Bottom() > b.Top()) &&
		(a.Top() < b.Bottom()))
	{
		return true;
	}

	return false;
}

bool
Collision::IsHit(Rect &r, Circle &c)
{
	//後で直す

	Rect horizonRect, verticalRect; //縦長の長方形と横長の長方形
	horizonRect = r;
	horizonRect.pos.x -= c.radius;
	horizonRect.w = r.w + c.radius;		//幅を設定

	verticalRect = r;
	verticalRect.pos.y -= c.radius;
	verticalRect.h = r.h + c.radius;	//高さを設定

	Vector2 leftUp, rightUp, leftDown, rightDown;

	//矩形の各頂点を設定する---------------------------------
	leftUp = Vector2(r.Left(), r.Top());
	rightUp = Vector2(r.Right(), r.Top());
	leftDown = Vector2(r.Left(), r.Bottom());
	rightDown = Vector2(r.Right(), r.Bottom());
	//-------------------------------------------------------

	//衝突判定-------------------------------------------------------------------
	if (CircleColToRect(horizonRect, c) || CircleColToRect(verticalRect, c))
	{
		return true;
	}
	return false;
	//---------------------------------------------------------------------------

}

bool
Collision::IsHit(Circle &c1, Circle &c2)
{
	bool hitFlag = false;
	float x = abs(c1.pos.x - c2.pos.x);
	float y = abs(c1.pos.y - c2.pos.y);

	if (x * x + y * y < c1.radius + c2.radius)
	{
		hitFlag = true;
	}
	return hitFlag;
}

bool 
Collision::IsHit(Rect &player, Block &block, Vector2 vec)
{
	bool hitFlag = false;
	Rect b = {};
	b.pos = block.GetRect().pos;
	b.w = block.GetRect().w;
	b.h = 10;

	Rect a = {};
	a.pos = player.pos;
	a.pos.y = player.Bottom() ;
	a.w = player.w;
	a.h = 10;

	if ((a.Right() > b.Left()) &&
		(a.Left() < b.Right()) &&
		(a.Bottom() > b.Top()) &&
		(a.Top() < b.Bottom()))
	{
		if (vec.y < 0)
		{
			return false;
		}
		hitFlag = true;
	}

	return hitFlag;

}
//bool 
//Collision::LineCross(Rect r1, Vector2 vec1, Rect r2,bool hitGround)
//{
//		if (vec1.y < 0)			 { _move = up; }
//		else if (vec1.y > 0 && !hitGround)	 { _move = down; }
//		else if (vec1.x < 0)	 { _move = left; }
//		else if (vec1.x > 0)	 { _move = right; }
//		else					 { _move = none; }
//
//		Vector2 p1[3], p2[3], p3, p4,freamVel;
//		float ta, tb, tc, td;
//
//		switch (_move)
//		{
//		case up:
//		{
//			int i = 0;
//			p1[i] = Vector2(r1.Left(), r1.Top());
//			p2[i] = p1[i];
//			p2[i].y += vec1.y;
//
//			++i;
//
//			p1[i] = Vector2(r1.Left() + r1.w / 2 , r1.Top());
//			p2[i] = p1[i];
//			p2[i].y += vec1.y;
//
//			++i;
//			p1[i] = Vector2(r1.Right(), r1.Top());
//			p2[i] = p1[i];
//			p2[i].y += vec1.y;
//			p3 = Vector2(r2.Left(), r2.Bottom());
//			p4 = Vector2(r2.Right(), r2.Bottom());
//		}
//		break;
//		case right:
//		{
//			int i = 0;
//			p1[i] = Vector2(r1.Right(), r1.Top());
//			p2[i] = p1[i];
//			p2[i].x += vec1.x;
//
//			++i;
//
//			p1[i] = Vector2(r1.Right(), r1.Top() + r1.h / 2);
//			p2[i] = p1[i];
//			p2[i].x += vec1.x;
//
//			++i;
//
//			p1[i] = Vector2(r1.Right(), r1.Bottom());
//			p2[i] = p1[i];
//			p2[i].x += vec1.x;
//
//			p3 = Vector2(r2.Left(), r2.Top() - r2.h / 2);
//			p4 = Vector2(r2.Left(), r2.Bottom() + r2.h / 2);
//		}
//		break;
//		case down:
//		{
//
//			int i = 0;
//			p1[i] = Vector2(r1.Left(), r1.Bottom());
//			p2[i] = p1[i];
//			p2[i].y += vec1.y;
//
//			++i;
//
//			p1[i] = Vector2(r1.Left() + r1.w / 2, r1.Bottom());
//			p2[i] = p1[i];
//			p2[i].y += vec1.y;
//
//			++i;
//
//			p1[i] = Vector2(r1.Right(), r1.Bottom());
//			p2[i] = p1[i];
//			p2[i].y += vec1.y;
//			p3 = Vector2(r2.Left(), r2.Top());
//			p4 = Vector2(r2.Right(), r2.Top());
//		}
//		break;
//		case left:
//		{
//			int i = 0;
//			p1[i] = Vector2(r1.Left(), r1.Top());
//			p2[i] = p1[i];
//			p2[i].x += vec1.x;
//
//			++i;
//
//			p1[i] = Vector2(r1.Left(), r1.Top() + r1.h / 2);
//			p2[i] = p1[i];
//			p2[i].x += vec1.x;
//
//			++i;
//			p1[i] = Vector2(r1.Left(), r1.Bottom());
//			p2[i] = p1[i];
//			p2[i].x += vec1.x;
//
//			p3 = Vector2(r2.Right() , r2.Top() - r2.h / 2);
//			p4 = Vector2(r2.Right(), r2.Bottom() + r2.h / 2);
//		}
//		break;
//		default:
//			break;
//		}
//
//		for (int i = 0; i < 3; i++)
//		{
//			ta = (p3.x - p4.x) * (p1[i].y - p3.y) + (p3.y - p4.y) * (p3.x - p1[i].x);
//			tb = (p3.x - p4.x) * (p2[i].y - p3.y) + (p3.y - p4.y) * (p3.x - p2[i].x);
//			tc = (p1[i].x - p2[i].x) * (p3.y - p1[i].y) + (p1[i].y - p2[i].y) * (p1[i].x - p3.x);
//			td = (p1[i].x - p2[i].x) * (p4.y - p1[i].y) + (p1[i].y - p2[i].y) * (p1[i].x - p4.x);
//			if (_move == up || _move == down)
//			{
//				if ((tc * td < 0 && ta * tb < 0))
//				{
//					return true;
//					break;
//				}
//			}
//			else
//			{
//				if ((tc * td < 0 && ta * tb < 0))
//				{
//					return true;
//					break;
//				}
//			}
//		}
//
//		if (r1.Bottom() == r2.Top() && (r1.Left() < r2.Right() && r1.Right() > r2.Left()))
//		{
//			return true;
//		}
//
//		return false;
//}

bool
Collision::LineCross(Rect character, Vector2 characterVec, Vector2 posB, Vector2 vecB)
{
	Vector2 characterPos;
	if (characterVec.y < 0)
	{
		if (characterVec.x > 0)
		{
			characterPos.x = character.Right();
			characterPos.y = character.Top();
		}
		else if (characterVec.x < 0)
		{
			characterPos = character.pos;
			characterPos.y = character.Top();
		}
		else
		{
			characterPos.x = character.pos.x + character.w / 2;
			characterPos.y = character.Top();
		}
	}
	else if (characterVec.y > 0)
	{
		if (characterVec.x > 0)
		{
			characterPos.x = character.Right();
			characterPos.y = character.Bottom();
		}
		else if (characterVec.x < 0)
		{
			characterPos = character.pos;
			characterPos.y = character.Bottom();
		}
		else
		{
			characterPos.x = character.pos.x + character.w / 2;
			characterPos.y = character.Bottom();
		}
	}
	else
	{
		if (characterVec.x > 0)
		{
			characterPos.x = character.Right();
			characterPos.y = character.Top() + character.h / 2;
		}
		else if (characterVec.x < 0)
		{
			characterPos = character.pos;
			characterPos.y = character.Top() + character.h / 2;
		}
		else
		{
			return false;
		}
	}

	float crsVaVb = cross(characterVec, vecB);
	if (crsVaVb == 0)
	{
		return false;
	}

	Vector2 v = posB - characterPos;
	float t1 = cross(v, characterVec);
	float t2 = cross(v, vecB);

	float t3 = t1 / crsVaVb;
	float t4 = t2 / crsVaVb;

	if (t3 < 0 || t3 > 1 || t4 < 0 || t4 > 1)
	{
		return false;
	}

	return true;
}

bool
Collision::LineCross(Rect characterA, Vector2 vecA, Rect characterB, Vector2 vecB)
{
	Vector2 characterPosA,characterPosB;

	//キャラクターAが動いているか判断--------------------------------------------
	if (vecA.y < 0)		//上向きに動いている場合
	{
		if (vecA.x > 0)				//右
		{
			characterPosA.x = characterA.Right();
			characterPosA.y = characterA.Top();
		}
		else if (vecA.x < 0)		//左
		{
			characterPosA = characterA.pos;
			characterPosA.y = characterA.Top();
		}
		else						//左右に動いていない
		{
			characterPosA.x = characterA.pos.x + characterA.w / 2;
			characterPosA.y = characterA.Top();
		}
	}
	else if (vecA.y > 0)//下向きに動いている場合
	{
		if (vecA.x > 0)				//右
		{
			characterPosA.x = characterA.Right();
			characterPosA.y = characterA.Bottom();
		}
		else if (vecA.x < 0)		//左
		{
			characterPosA = characterA.pos;
			characterPosA.y = characterA.Bottom();
		}
		else						//左右に動いていない
		{
			characterPosA.x = characterA.pos.x + characterA.w / 2;
			characterPosA.y = characterA.Bottom();
		}
	}
	else			//上下に動いていない場合
	{
		if (vecA.x > 0)				//右
		{
			characterPosA.x = characterA.Right();
			characterPosA.y = characterA.Top() + characterA.h / 2;
		}
		else if (vecA.x < 0)		//左
		{
			characterPosA = characterA.pos;
			characterPosA.y = characterA.Top() + characterA.h / 2;
		}
		else						//移動していない
		{
			return false;			//移動していないならベクトルは交差しない
		}
	}
	//---------------------------------------------------------------------------

	//キャラクターBが動いているか判断--------------------------------------------
	if (vecB.y < 0)		//上向きに動いている場合
	{
		if (vecB.x > 0)				//右
		{
			characterPosB.x = characterB.Right();
			characterPosB.y = characterB.Top();
		}
		else if (vecB.x < 0)		//左
		{
			characterPosB = characterB.pos;
			characterPosB.y = characterB.Top();
		}
		else						//左右に動いていない
		{
			characterPosB.x = characterB.pos.x + characterB.w / 2;
			characterPosB.y = characterB.Top();
		}
	}
	else if (vecB.y > 0)//下向きに動いている場合
	{
		if (vecB.x > 0)				//右
		{
			characterPosB.x = characterB.Right();
			characterPosB.y = characterB.Bottom();
		}
		else if (vecB.x < 0)		//左
		{
			characterPosB = characterB.pos;
			characterPosB.y = characterB.Bottom();
		}
		else						//左右に動いていない
		{
			characterPosB.x = characterB.pos.x + characterB.w / 2;
			characterPosB.y = characterB.Bottom();
		}
	}
	else			//上下に動いていない場合
	{
		if (vecB.x > 0)				//右
		{
			characterPosB.x = characterB.Right();
			characterPosB.y = characterB.Top() + characterB.h / 2;
		}
		else if (vecB.x < 0)		//左
		{
			characterPosB = characterB.pos;
			characterPosB.y = characterB.Top() + characterB.h / 2;
		}
		else						//移動していない
		{
			return false;			//移動していないならベクトルは交差しない
		}
	}
	//---------------------------------------------------------------------------

	float crsVaVb = cross(vecA, vecB);
	if (crsVaVb == 0)
	{
		return false;
	}

	Vector2 v = characterPosB - characterPosA;
	float t1 = cross(v, vecA);
	float t2 = cross(v, vecB);

	float t3 = t1 / crsVaVb;
	float t4 = t2 / crsVaVb;

	if (t3 < 0 || t3 > 1 || t4 < 0 || t4 > 1)
	{
		return false;
	}

	return true;
}

bool
Collision::LinerInterpolation(Rect& rect, Vector2& velocityA, Circle& circle, Vector2& velocityB)
{
	bool moveRightA = true;		//とりあえず右向きに動いているものとする

	if (velocityA.x < 0)		//左向きに動いているのなら
	{
		moveRightA = false;
	}
	else if (velocityA.x == 0)	//動いていないなら線形補間は必要ないので
	{
		return false;
	}

	float time = 0.1f;
	Vector2 nextPosA, nextPosB;
	nextPosA = rect.pos;
	nextPosB = circle.pos;
	if (velocityA.x * velocityB.x < 0)
	{
		while (time < 10)
		{
			nextPosA.x = (rect.pos.x + (rect.pos.x + velocityA.x)) * time;
			nextPosB.x = (circle.pos.x + (circle.pos.x + velocityB.x)) * time;

			if (moveRightA)
			{
				if (nextPosA.x >= nextPosB.x && CircleColToRect(rect,circle))
				{
					return true;
				}
				else
				{
					time++;
					continue;
				}
			}
			else
			{
				if (nextPosA.x <= nextPosB.x && CircleColToRect(rect, circle))
				{
					return true;
				}
				else
				{
					time++;
					continue;
				}
			}
		}
	}
	return false;
}

bool CircleColToRect(Rect &a, Circle &c)
{
	if ((a.Left() < c.pos.x && a.Top() < c.pos.y) &&
		(a.Left() < c.pos.x && a.Bottom() > c.pos.y) &&
		(a.Right() > c.pos.x && a.Top() < c.pos.y) &&
		(a.Right() > c.pos.x && a.Bottom() > c.pos.y))
	{
		return true;
	}
	
	return false;
}

float DistanceCalcuration(Vector2 &v1, Vector2 &v2)
{
	float distance = 0;
	float distance2 = 0;
	float x, y;

	x = abs(v1.x - v2.x);
	y = abs(v1.y - v2.y);

	return distance = sqrt(x * x + y * y);
}
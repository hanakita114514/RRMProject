#include "Collision.h"
#include "RectObj.h"
#include "CircleObj.h"
#include "Player.h"
#include <math.h> 
#include "Enemy.h"

Collision::Collision()
{
	_move = none;
}


Collision::~Collision()
{
}


bool Collision::IsHit(Rect &a, Rect &b)
{
	bool hitFlag = false;

	if ((a.Right() > b.Left()) &&
		(a.Left() < b.Right()) &&
		(a.Bottom() > b.Top()) &&
		(a.Top() < b.Bottom()))
	{
		hitFlag = true;
	}

	return hitFlag;
}

bool
Collision::IsHit(Rect &r, Circle &c)
{
	//後で直す
	bool hitFlag = false;
	float x = abs(r.pos.x - c.pos.x);
	float y = abs(r.pos.y - c.pos.y);

	float dist = sqrt(x * x + y * y);
	
	if (dist < r.h + c.radius )
	{
		hitFlag = true;
	}

	return hitFlag;
}

bool
Collision::IsHit(Circle &c1, Circle &c2)
{
	bool hitFlag = false;
	float x = abs(c1.pos.x - c2.pos.x);
	float y = abs(c1.pos.y - c2.pos.y);

	float dist = sqrt(x * x + y * y);

	if (dist < c1.radius + c2.radius)
	{
		hitFlag = true;
	}
	return hitFlag;
}

bool 
Collision::LineCross(Rect r1, Vector2 vec1, Rect r2,bool hitGround)
{
		if (vec1.y < 0)			 { _move = up; }
		else if (vec1.y > 0 && !hitGround)	 { _move = down; }
		else if (vec1.x < 0)	 { _move = left; }
		else if (vec1.x > 0)	 { _move = right; }
		else					 { _move = none; }

		Vector2 p1[3], p2[3], p3, p4,freamVel;
		float ta, tb, tc, td;

		switch (_move)
		{
		case up:
		{
			int i = 0;
			p1[i] = Vector2(r1.Left(), r1.Top());
			p2[i] = p1[i];
			p2[i].y += vec1.y;

			++i;

			p1[i] = Vector2(r1.Left() + r1.w / 2 , r1.Top());
			p2[i] = p1[i];
			p2[i].y += vec1.y;

			++i;
			p1[i] = Vector2(r1.Right(), r1.Top());
			p2[i] = p1[i];
			p2[i].y += vec1.y;
			p3 = Vector2(r2.Left(), r2.Bottom());
			p4 = Vector2(r2.Right(), r2.Bottom());
		}
		break;
		case right:
		{
			int i = 0;
			p1[i] = Vector2(r1.Right(), r1.Top());
			p2[i] = p1[i];
			p2[i].x += vec1.x;

			++i;

			p1[i] = Vector2(r1.Right(), r1.Top() + r1.h / 2);
			p2[i] = p1[i];
			p2[i].x += vec1.x;

			++i;

			p1[i] = Vector2(r1.Right(), r1.Bottom());
			p2[i] = p1[i];
			p2[i].x += vec1.x;

			p3 = Vector2(r2.Left(), r2.Top() - r2.h / 2);
			p4 = Vector2(r2.Left(), r2.Bottom() + r2.h / 2);
		}
		break;
		case down:
		{

			int i = 0;
			p1[i] = Vector2(r1.Left(), r1.Bottom());
			p2[i] = p1[i];
			p2[i].y += vec1.y;

			++i;

			p1[i] = Vector2(r1.Left() + r1.w / 2, r1.Bottom());
			p2[i] = p1[i];
			p2[i].y += vec1.y;

			++i;

			p1[i] = Vector2(r1.Right(), r1.Bottom());
			p2[i] = p1[i];
			p2[i].y += vec1.y;
			p3 = Vector2(r2.Left(), r2.Top());
			p4 = Vector2(r2.Right(), r2.Top());
		}
		break;
		case left:
		{
			int i = 0;
			p1[i] = Vector2(r1.Left(), r1.Top());
			p2[i] = p1[i];
			p2[i].x += vec1.x;

			++i;

			p1[i] = Vector2(r1.Left(), r1.Top() + r1.h / 2);
			p2[i] = p1[i];
			p2[i].x += vec1.x;

			++i;
			p1[i] = Vector2(r1.Left(), r1.Bottom());
			p2[i] = p1[i];
			p2[i].x += vec1.x;

			p3 = Vector2(r2.Right() , r2.Top() - r2.h / 2);
			p4 = Vector2(r2.Right(), r2.Bottom() + r2.h / 2);
		}
		break;
		default:
			break;
		}

		for (int i = 0; i < 3; i++)
		{
			ta = (p3.x - p4.x) * (p1[i].y - p3.y) + (p3.y - p4.y) * (p3.x - p1[i].x);
			tb = (p3.x - p4.x) * (p2[i].y - p3.y) + (p3.y - p4.y) * (p3.x - p2[i].x);
			tc = (p1[i].x - p2[i].x) * (p3.y - p1[i].y) + (p1[i].y - p2[i].y) * (p1[i].x - p3.x);
			td = (p1[i].x - p2[i].x) * (p4.y - p1[i].y) + (p1[i].y - p2[i].y) * (p1[i].x - p4.x);
			if (_move == up || _move == down)
			{
				if ((tc * td < 0 && ta * tb < 0))
				{
					return true;
					break;
				}
			}
			else
			{
				if ((tc * td < 0 && ta * tb < 0))
				{
					return true;
					break;
				}
			}
		}

		if (r1.Bottom() == r2.Top() && (r1.Left() < r2.Right() && r1.Right() > r2.Left()))
		{
			return true;
		}

		return false;
}

bool
Collision::LineCross(Rect rA, Vector2 vecA, Rect rB, Vector2 vecB)
{
	Vector2 startPointA, endPointA;		//ベクトルAの始点と終点
	Vector2 startPointB, endPointB;		//ベクトルBの始点と終点

	//ベクトルAが左向きか？
	if (vecA.x < 0)
	{
		startPointA = rA.pos;
	}
	else
	{
		startPointA = rA.pos;
		startPointA.x = rA.Right();
	}

	//ベクトルBが左向きか？
	if (vecB.x < 0)
	{
		startPointB = rB.pos;
	}
	else
	{
		startPointB = rB.pos;
		startPointB.x = rB.Right();
	}

	//終点を設定----------------------------------
	endPointA = startPointA + vecA;
	endPointB = startPointB + vecB;
	//--------------------------------------------

	//交差判定------------------------------------
	if ((cross(endPointA - startPointA, startPointB - startPointA) *
		cross(endPointA - startPointA, endPointB - startPointA) < 0) &&
		cross(endPointB - startPointB, startPointA - startPointB) *
		cross(endPointB - startPointB, endPointA - startPointB) < 0)
	{
		return true;
	}
	
	return false;
}

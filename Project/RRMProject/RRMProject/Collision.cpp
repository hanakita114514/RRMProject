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
//�~����`�ɓ������Ă��邩�ǂ���
bool CircleColToRect(Rect &a, Circle &c); 

//2�_�Ԃ̋��������߂�
float DistanceCalcuration(Vector2 &v1, Vector2 &v2);

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
	//��Œ���
	bool hitFlag = false;

	Rect horizonRect, verticalRect; //�c���̒����`�Ɖ����̒����`
	horizonRect = r;
	horizonRect.pos.x -= c.radius;
	horizonRect.w = r.w + c.radius * 2;		//����ݒ�

	verticalRect = r;
	verticalRect.pos.y -= c.radius;
	verticalRect.h = r.h + c.radius * 2;	//������ݒ�

	Vector2 leftUp, rightUp, leftDown, rightDown;

	//��`�̊e���_��ݒ肷��---------------------------------
	leftUp = Vector2(r.Left(), r.Top());
	rightUp = Vector2(r.Right(), r.Top());
	leftDown = Vector2(r.Left(), r.Bottom());
	rightDown = Vector2(r.Right(), r.Bottom());
	//-------------------------------------------------------

	//�Փ˔���-------------------------------------------------------------------
	if (CircleColToRect(horizonRect, c) || CircleColToRect(verticalRect, c))
	{
		if ((DistanceCalcuration(leftUp, c.pos) < (c.radius * c.radius)) &&
			(DistanceCalcuration(rightUp, c.pos) < (c.radius * c.radius)) &&
			(DistanceCalcuration(leftDown, c.pos) < (c.radius * c.radius)) &&
			(DistanceCalcuration(rightDown, c.pos) < (c.radius * c.radius)))
		{
			hitFlag = true;
		}
	}
	//---------------------------------------------------------------------------

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
Collision::LineCross(Vector2 posA, Vector2 vecA, Vector2 posB, Vector2 vecB)
{
	Vector2 startPointA, endPointA;		//�x�N�g��A�̎n�_�ƏI�_
	Vector2 startPointB, endPointB;		//�x�N�g��B�̎n�_�ƏI�_

	////�x�N�g��A�����������H
	//if (vecA.x < 0)
	//{
	//	startPointA = rA.pos;
	//}
	//else
	//{
	//	startPointA = rA.pos;
	//	startPointA.x = rA.Right();
	//}

	////�x�N�g��B�����������H
	//if (vecB.x < 0)
	//{
	//	startPointB = rB.pos;
	//}
	//else
	//{
	//	startPointB = rB.pos;
	//	startPointB.x = rB.Right();
	//}

	////�I�_��ݒ�----------------------------------
	//endPointA = startPointA + vecA;
	//endPointB = startPointB + vecB;
	////--------------------------------------------

	////��������------------------------------------
	//if ((cross(endPointA - startPointA, startPointB - startPointA) *
	//	cross(endPointA - startPointA, endPointB - startPointA) < 0) &&
	//	cross(endPointB - startPointB, startPointA - startPointB) *
	//	cross(endPointB - startPointB, endPointA - startPointB) < 0)
	//{
	//	return true;
	//}
	//
	//return false;

	//startPointA = posA;
	//startPointB = posB;
	//endPointA = startPointA + vecA;
	//endPointB = startPointB + vecB;

	//if ((cross(endPointA - startPointA, startPointB - startPointA) *
	//	cross(endPointA - startPointA, endPointB - startPointA) < 0) &&
	//	cross(endPointB - startPointB, startPointA - startPointB) *
	//	cross(endPointB - startPointB, endPointA - startPointB) < 0)
	//{
	//	return true;
	//}

	float crsVaVb = cross(vecA, vecB);
	if (crsVaVb == 0)
	{
		return false;
	}

	Vector2 v = posB - posA;
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
	float x, y;

	x = abs(v1.x - v2.x);
	y = abs(v1.y - v2.y);

	return distance = sqrt(x * x + y * y);
}
#include "Collision.h"
#include "RectObj.h"
#include "CircleObj.h"
#include "Player.h"
#include <math.h> 
#include "Enemy.h"

Collision::Collision()
{
	sink = Vector2(0, 0);			//‚ß‚èž‚ñ‚¾—Ê
	_move = none;
}


Collision::~Collision()
{
}


bool Collision::IsHit(Rect &a, Rect &b)
{
	bool hitFlug = false;

	float absX = abs(a.pos.x - b.pos.x);
	float absY = abs(a.pos.y - b.pos.y);

	int x = a.w / 2 + b.w / 2;
	int y = a.h / 2 + b.h / 2;

	if(x >= absX && y >= absY)
	{
		hitFlug = true;
	}

	return hitFlug;
}

bool
Collision::IsHit(Rect &r, Circle &c)
{
	bool hitFlug = false;
	float x = abs(r.pos.x - c.pos.x);
	float y = abs(r.pos.y - c.pos.y);

	float dist = sqrt(x * x + y * y);
	
	if (dist < r.h + c.radius && (r.pos.x < c.pos.x && c.pos.x < r.Right()))
	{
		hitFlug = true;
	}

	return hitFlug;
}

bool
Collision::IsHit(Circle &c1, Circle &c2)
{
	bool hitFlug = false;
	float x = abs(c1.pos.x - c2.pos.x);
	float y = abs(c1.pos.y - c2.pos.y);

	float dist = sqrt(x * x + y * y);

	if (dist < c1.radius + c2.radius)
	{
		hitFlug = true;
	}
	return hitFlug;
}

void Collision::PushBack(Rect r,Player &p)
{
	Rect pr = p.GetRect();
	Vector2 vel = p.GetVel();
	if (sink.y < sink.x)
	{
		if (vel.y > 0)
		{
			pr.SetBottom(r.Top());
			p.SetHitGround(true);
		}
		else if(vel.y < 0)
		{
			pr.SetTop(r.Bottom());
		}
	}
	else
	{
		if (vel.x > 0)
		{
			pr.SetRight(r.Left());
		}
		else if( vel.x < 0)
		{
			pr.SetLeft(r.Right());
		}
	}
	p.SetPos(pr);
}

void Collision::PushBack(Rect r, Enemy &e)
{
	Rect er = e.GetRect();
	Vector2 vel = e.GetVel();
	if (sink.y < sink.x)
	{
		if (vel.y > 0)
		{
			er.SetBottom(r.Top());
			e.SetHitGround(true);
		}
		else if( vel.y < 0)
		{
			er.SetTop(r.Bottom());
		}
	}
	else
	{
		if (vel.x > 0)
		{
			er.SetRight(r.Left());
		}
		else if(vel.x < 0)
		{
			er.SetLeft(r.Right());
		}
	}
	e.SetPos(er);
}


bool 
Collision::LineCross(Rect r1, Vector2 vec1, Rect r2)
{
	if (r1.Bottom() == r2.Top() && (r1.Left() < r2.Right() && r1.Right() > r2.Left()) && vec1.x == 0)
	{
		return true;
	}
	else
	{
		if (vec1.y < 0) _move = up;
		else if (vec1.y > 0) _move = down;
		else if (vec1.x < 0) _move = left;
		else if (vec1.x > 0) _move = right;
		else _move = none;

		Vector2 p1[3], p2[3], p3, p4;
		float ta, tb, tc, td;

		switch (_move)
		{
		case up:
		{
			int i = 0;
			p1[i] = Vector2(r1.Left(), r1.Top());
			p2[i] = p1[i];
			p2[i].y -= vec1.y;

			++i;

			p1[i] = Vector2(r1.Left() + r1.w / 2 , r1.Top());
			p2[i] = p1[i];
			p2[i].y -= vec1.y;

			++i;
			p1[i] = Vector2(r1.Right(), r1.Top());
			p2[i] = p1[i];
			p2[i].y -= vec1.y;
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

			p1[i] = Vector2(r1.Left() + r1.w / 2, r1.Top());
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

			p1[i] = Vector2(r1.Left() + r1.w / 2, r1.Top());
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
			p2[i].x -= vec1.x;

			++i;

			p1[i] = Vector2(r1.Left() + r1.w / 2, r1.Top());
			p2[i] = p1[i];
			p2[i].x -= vec1.x;

			++i;
			p1[i] = Vector2(r1.Left(), r1.Bottom());
			p2[i] = p1[i];
			p2[i].x -= vec1.x;

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

			if (tc * td < 0 && ta * tb < 0)
			{
				return true;
				break;
			}
		}
		return false;
	}
}

void 
Collision::PushBack(Rect &ra, Rect &rb,Vector2 vecA)
{
	Rect r = ra;
	Vector2 vel = vecA;
	if (sink.y < sink.x)
	{
		if (vel.y > 0)
		{
			r.SetBottom(rb.Top());
		}
		else if (vel.y < 0)
		{
			r.SetTop(rb.Bottom());
		}
	}
	else
	{
		if (vel.x > 0)
		{
			r.SetRight(rb.Left());
		}
		else if (vel.x < 0)
		{
			r.SetLeft(rb.Right());
		}
	}
	ra = r;
}


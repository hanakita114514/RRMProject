#pragma once
#include "BulletFactory.h"
#include "Vector2.h"
#include "Circle.h"
class Bullet;

class Spell
{
private:
	BulletFactory _bulletFactory;
	Vector2 _vec,_pos;
	Circle _circle;



public:
	Spell();
	~Spell();

	void TestSpell(Vector2 vec,Vector2 pos,Object* owner);
	void CircleShot(Vector2 vec, Vector2 pos, Object* owner);
};


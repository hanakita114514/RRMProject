#pragma once
#include "Vector2.h"
#include "Circle.h"
#include "Object.h"

class Spell
{
private:
	Vector2 _vec,_pos;
	Circle _circle;
	float _freamCnt;

	Bullet* prevBullet;
public:
	Spell();
	~Spell();

	void TestSpell(Vector2 vec,Vector2 pos,Object* owner);
	void CircleShot(Vector2 vec, Vector2 pos, Object* owner);
	void Comet(Vector2 vec, Vector2 pos, Object* owner);
};


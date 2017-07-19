#pragma once
#include "Bullet.h"
#include <random>
class DeffusionBullet :  public Bullet
{
private:
	bool _defFlug;
	Vector2 _vec;
	Vector2 _randVec;
	int _freamCnt;

public:
	DeffusionBullet(int handle);
	~DeffusionBullet();

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Update();
	void Draw(const Vector2& offset);

	void Move();

	void Deffusion();
};


#pragma once
#include "Bullet.h"

class CircleBullet : public Bullet
{
private:
	float _rad;			//Šp“x
	Vector2 _shotPos;


	float _fream;

	bool stopFlag;

public:
	CircleBullet(int handle);
	~CircleBullet();

	void Update();
	void Draw(const Vector2& offset);
	void Initialize(const Position& pos, Vector2 vec, ObjectType type);

};


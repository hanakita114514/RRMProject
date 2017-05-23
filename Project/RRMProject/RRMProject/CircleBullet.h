#pragma once
#include "Bullet.h"
class CircleBullet : public Bullet
{
private:
	float _rad;			//Šp“x
	Vector2 _shotPos;
public:
	CircleBullet(int handle);
	~CircleBullet();

	void Update();
	void Draw();
	void Initialize(Vector2 vec, ObjectType type);

	void Move();
};


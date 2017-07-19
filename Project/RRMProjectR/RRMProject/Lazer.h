#pragma once
#include "Bullet.h"

const int IMAGE_MAX = 7;
const int IMAGE_SIZE_X = 20;
const int IMAGE_SIZE_Y = 256;

class Lazer : public Bullet
{
private:
	int _handle[IMAGE_MAX];
	int _frameCnt;
	Vector2 _vec;
	Vector2 _etyPoint, _endPoint, _ctlPoint;
public:
	Lazer();
	~Lazer();

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Initialize();
	void Update();
	void Draw(const Vector2& offset);
};


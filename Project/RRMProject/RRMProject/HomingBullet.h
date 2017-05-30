#pragma once
#include "Bullet.h"

const float PI = 3.14;
class HomingBullet : public Bullet
{
private:

	Position* _targetPos;
	Position* _ownPos;
	float _center;
	int _homCnt;
public:
	HomingBullet(int handle,Vector2 vec);
	~HomingBullet(); 

	void Initialize(Vector2 vec, ObjectType type);
	void Update();
	void Draw(const Vector2& offset);

	void Move();
	void LifeDecrease();
};


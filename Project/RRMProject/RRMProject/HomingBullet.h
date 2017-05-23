#pragma once
#include "Bullet.h"

const float PI = 3.14;
class HomingBullet : public Bullet
{
private:

	Position* _pPos;
	Position* _ePos;
	float _center;
	int _homCnt;
public:
	HomingBullet(int handle,Vector2 vec);
	~HomingBullet(); 

	void Initialize(Vector2 vec, ObjectType type);
	void Update();
	void Draw();

	void Move();
	void LifeDecree();

	void SetAngle(Vector2* pPos, Vector2* ePos);
};


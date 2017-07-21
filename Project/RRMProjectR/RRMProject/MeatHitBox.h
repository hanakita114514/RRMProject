#pragma once
#include "EnemyHitBox.h"
class MeatHitBox : public EnemyHitBox
{
public:
	MeatHitBox();
	~MeatHitBox();

	void Search(float frame, const Rect& rc, const Vector2& dir);
};


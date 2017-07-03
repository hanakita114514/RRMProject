#pragma once

#include "EnemyHitBox.h"

class SushiHitBox : public EnemyHitBox
{
public:
	SushiHitBox();
	~SushiHitBox();

	void Search(float frame, const Rect& rc, const Vector2& dir);
	void Foot(float frame, const Rect& rc, const Vector2& dir);
	void Attack(float frame, const Rect& rc, const Vector2& dir);
};


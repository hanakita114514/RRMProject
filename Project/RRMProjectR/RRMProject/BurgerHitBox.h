#pragma once

#include "EnemyHitBox.h"

class BurgerHitBox : public EnemyHitBox
{
public:
	BurgerHitBox();
	~BurgerHitBox();

	void Search(float frame, const Rect& rc, const Vector2& dir);
	void Foot(float frame, const Rect& rc, const Vector2& dir);
	void Attack(float frame, const Rect& rc, const Vector2& dir);
};


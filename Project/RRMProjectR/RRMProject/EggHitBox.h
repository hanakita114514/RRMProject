#pragma once
#include "EnemyHitBox.h"

class EggHitBox : public EnemyHitBox
{
public:
	EggHitBox();
	~EggHitBox();

	 void Search(float frame, const Rect& rc, const Vector2& dir);
	 void Foot(float frame, const Rect& rc, const Vector2& dir);

};


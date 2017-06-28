#pragma once

#include "Rect.h"

struct HitBox
{
	Rect rc;				//当たり判定
	float power;			//攻撃力
	float hitstop;			//ヒットストップ時間
	Vector2 vec;			//吹っ飛ばしベクトル

	HitBox();
	HitBox(float power, float hitstop, const Rect& rc, const Vector2& vec = Vector2(0,0));
};

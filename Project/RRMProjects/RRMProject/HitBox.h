#pragma once

#include "Rect.h"

struct HitBox
{
	Rect rc;				//攻撃判定
	float power;			//攻撃力
	float hitstop;			//ヒットストップ時間

	HitBox();
	HitBox(float power, float hitstop, Rect rc);
};

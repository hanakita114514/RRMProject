#pragma once

#include "Rect.h"

struct HitBox
{
	Rect rc;				//�U������
	float power;			//�U����
	float hitstop;			//�q�b�g�X�g�b�v����

	HitBox();
	HitBox(float power, float hitstop, Rect rc);
};

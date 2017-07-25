#pragma once

#include "Rect.h"

struct HitBox
{
	Rect rc;				//�����蔻��
	float power;			//�U����
	float hitstop;			//�q�b�g�X�g�b�v����
	Vector2 vec;			//������΂��x�N�g��
	Vector2 dir;			//����

	HitBox();
	HitBox(float power, float hitstop, const Rect& rc, const Vector2& vec = Vector2(0,0), const Vector2& dir = Vector2(0,0));
};

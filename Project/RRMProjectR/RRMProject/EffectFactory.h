#pragma once

#include "Vector2.h"
class Effect;
#include <map>

enum class EffectType : unsigned int
{
	//�Ȃ�
	none,

	//�����ɒǉ�
	up,
	down,
	flash,
	explosion,
	erasure,
	bullet_summons,
	enemy_summons,
	hit1,
	slash,
	star,
	hit2,

	num,

};

class EffectFactory
{
private:
	std::map<EffectType, int> _effectImg;

public:
	EffectFactory();
	~EffectFactory();

	Effect* Create(EffectType et, const Position& pos, const Vector2& size, float speed, bool isLoop);
};


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

};

class EffectFactory
{
private:
	std::map<EffectType, int> _effectImg;

public:
	EffectFactory();
	~EffectFactory();

	Effect* Create(EffectType et, const Position& pos);
};


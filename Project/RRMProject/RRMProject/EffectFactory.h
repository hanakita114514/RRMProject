#pragma once

#include "Vector2.h"
class Effect;
#include <map>

enum class EffectType : unsigned int
{
	//なし
	none,


	//ここに追加
	up,
	down,
	flash,

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


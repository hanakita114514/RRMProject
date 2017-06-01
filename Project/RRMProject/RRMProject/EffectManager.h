#pragma once

#include "EffectFactory.h"
#include <vector>
#include <map>

class Effect;

class EffectManager
{
private:
	std::vector<Effect*> _effectList;

	EffectFactory _effectFactory;

public:
	EffectManager();
	~EffectManager();

	void Update();
	void Draw(const Vector2& offset);

	void Create(EffectType et, const Position& pos);

	std::vector<Effect*>& GetEffectList() { return _effectList; }

	void Delete();
};


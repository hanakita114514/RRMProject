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

	EffectManager();
	EffectManager(const EffectManager&);
	EffectManager& operator = (const EffectManager&);
public:
	~EffectManager();

	static EffectManager& Instance()
	{
		static EffectManager instance;
		return instance;
	}

	void Update();
	//íÜêSï`âÊ
	void Draw(const Vector2& offset);

	Effect* Create(EffectType et, const Position& pos, const Vector2& size = Vector2(1.0f, 1.0f), float speed = 1.0f, bool isLoop = false);

	std::vector<Effect*>& GetEffectList() { return _effectList; }

	void Delete();
};


#include "EffectManager.h"
#include "Effect.h"

EffectManager::EffectManager()
{

}


EffectManager::~EffectManager()
{
}

void 
EffectManager::Update()
{
	for (auto& e : _effectList)
	{
		e->Update();
	}

	auto itr = _effectList.begin();

	for (; itr != _effectList.end();)
	{
		if ((*itr)->IsDelete())
		{
			delete (*itr);
			*itr = nullptr;
			itr = _effectList.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void 
EffectManager::Draw(const Vector2& offset)
{
	for (auto& e : _effectList)
	{
		e->Draw(offset);
	}
}

Effect*
EffectManager::Create(EffectType et, const Position& pos, const Vector2& size, float speed, bool isLoop)
{
	_effectList.push_back(_effectFactory.Create(et, pos, size, speed, isLoop));
	return _effectList.back();
}

void
EffectManager::Delete()
{
	auto itr = _effectList.begin();

	for (; itr != _effectList.end();)
	{
		delete (*itr);
		*itr = nullptr;
		itr = _effectList.erase(itr);
	}
}
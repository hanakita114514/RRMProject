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

void 
EffectManager::Create(EffectType et, const Position& pos)
{
	_effectList.push_back(_effectFactory.Create(et, pos));
}

void
EffectManager::Delete()
{
	auto itr = _effectList.begin();

	for (; itr != _effectList.end();)
	{
		delete (*itr);
		*itr = nullptr;
		_effectList.erase(itr);
	}
}
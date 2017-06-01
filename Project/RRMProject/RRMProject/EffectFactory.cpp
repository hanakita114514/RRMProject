#include "EffectFactory.h"
#include "UpEffect.h"
#include <DxLib.h>


EffectFactory::EffectFactory()
{
	_effectImg[EffectType::up] = DxLib::LoadGraph("Resource/img/Effect/UP.png");
}


EffectFactory::~EffectFactory()
{
}

Effect*
EffectFactory::Create(EffectType et, const Position& pos)
{
	switch (et)
	{
	case EffectType::none:
		return nullptr;
		break;
	case EffectType::up:
		return new UpEffect(_effectImg[EffectType::up]);
		break;
	case EffectType::down:
		break;
	default:
		return nullptr;
		break;
	}

	return nullptr;
}
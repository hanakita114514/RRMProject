#include "EffectFactory.h"
#include "UpEffect.h"
#include "DownEffect.h"
#include "GeneralEffect.h"
#include <DxLib.h>


EffectFactory::EffectFactory()
{
	_effectImg[EffectType::up] = DxLib::LoadGraph("Resource/img/Effect/UP.png");
	_effectImg[EffectType::down] = DxLib::LoadGraph("Resource/img/Effect/Down.png");
	_effectImg[EffectType::flash] = DxLib::LoadGraph("Resource/img/Effect/Flash.png");

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
		return new UpEffect(_effectImg[EffectType::up], pos);
		break;
	case EffectType::down:
		return new DownEffect(_effectImg[EffectType::down], pos);
		break;
	case EffectType::flash:
		//•Û—¯
		//return new GeneralEffect(_effectImg[EffectType::flash], pos, 1280, 1536, 6, 5);
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}

	return nullptr;
}
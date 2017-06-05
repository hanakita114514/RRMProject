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
	_effectImg[EffectType::explosion] = DxLib::LoadGraph("Resource/img/Effect/Explosion.png");
	_effectImg[EffectType::erasure] = DxLib::LoadGraph("Resource/img/Effect/erasure.png");
	_effectImg[EffectType::enemy_summons] = DxLib::LoadGraph("Resource/img/Effect/summons.png");
	_effectImg[EffectType::bullet_summons] = DxLib::LoadGraph("Resource/img/Effect/MagicCircle1.png");
	_effectImg[EffectType::hit1] = DxLib::LoadGraph("Resource/img/Effect/hit.png");
	_effectImg[EffectType::slash] = DxLib::LoadGraph("Resource/img/Effect/Srash.png");
	_effectImg[EffectType::star] = DxLib::LoadGraph("Resource/img/Effect/star.png");
	_effectImg[EffectType::hit2] = DxLib::LoadGraph("Resource/img/Effect/hit2.png");
}


EffectFactory::~EffectFactory()
{
}

Effect*
EffectFactory::Create(EffectType et, const Position& pos, const Vector2& size, float speed, bool isLoop)
{
	switch (et)
	{
	case EffectType::none:
		return nullptr;
		break;
	case EffectType::up:
		return new UpEffect(_effectImg[EffectType::up], pos, size);
		break;
	case EffectType::down:
		return new DownEffect(_effectImg[EffectType::down], pos, size);
		break;
	case EffectType::flash:
		//•Û—¯
		return new GeneralEffect(_effectImg[EffectType::flash], pos, 1280, 1536, 6, 5, speed, size, isLoop);
		//return nullptr;
		break;
	case EffectType::explosion:
		return new GeneralEffect(_effectImg[EffectType::explosion], pos, 1280, 1536, 6, 5, speed, size, isLoop);
		break;
	case EffectType::erasure:
		return new GeneralEffect(_effectImg[EffectType::erasure], pos, 1280, 1536, 6, 5, speed, size, isLoop);
		break;
	case EffectType::bullet_summons:
		return new GeneralEffect(_effectImg[EffectType::bullet_summons], pos, 1280, 1536, 6, 5, speed, size, isLoop);
		break;
	case EffectType::enemy_summons:
		return new GeneralEffect(_effectImg[EffectType::enemy_summons], pos, 1280, 1536, 6, 5, speed, size, isLoop);
		break;
	case EffectType::hit1:
		return new GeneralEffect(_effectImg[EffectType::hit1], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	case EffectType::slash:
		return new GeneralEffect(_effectImg[EffectType::slash], pos, 768, 512, 2, 3, 1.0f, size, isLoop);
		break;
	case EffectType::star:
		return new GeneralEffect(_effectImg[EffectType::star], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	case EffectType::hit2:
		return new GeneralEffect(_effectImg[EffectType::hit2], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	default:
		return nullptr;
		break;
	}

	return nullptr;
}
#include "EffectFactory.h"
#include "UpEffect.h"
#include "DownEffect.h"
#include "GeneralEffect.h"
#include <RRMLib.h>

EffectFactory::EffectFactory()
{
	_effectImg[EffectType::up] = RRMLib::LoadGraph("Resource/img/Effect/UP.png");
	_effectImg[EffectType::down] = RRMLib::LoadGraph("Resource/img/Effect/Down.png");
	_effectImg[EffectType::flash] = RRMLib::LoadGraph("Resource/img/Effect/Flash.png");
	_effectImg[EffectType::explosion] = RRMLib::LoadGraph("Resource/img/Effect/Explosion.png");
	_effectImg[EffectType::erasure] = RRMLib::LoadGraph("Resource/img/Effect/erasure.png");
	_effectImg[EffectType::enemy_summons] = RRMLib::LoadGraph("Resource/img/Effect/summons.png");
	_effectImg[EffectType::bullet_summons] = RRMLib::LoadGraph("Resource/img/Effect/MagicCircle1.png");
	_effectImg[EffectType::hit1] = RRMLib::LoadGraph("Resource/img/Effect/hit.png");
	_effectImg[EffectType::slash] = RRMLib::LoadGraph("Resource/img/Effect/Srash.png");
	_effectImg[EffectType::star] = RRMLib::LoadGraph("Resource/img/Effect/star.png");
	_effectImg[EffectType::hit2] = RRMLib::LoadGraph("Resource/img/Effect/hit2.png");
	_effectImg[EffectType::defeat] = RRMLib::LoadGraph("Resource/img/Effect/defeat.png");
	_effectImg[EffectType::emergence] = RRMLib::LoadGraph("Resource/img/Effect/emergence.png");
	_effectImg[EffectType::slash2] = RRMLib::LoadGraph("Resource/img/Effect/slash2.png");
	_effectImg[EffectType::focusing] = RRMLib::LoadGraph("Resource/img/Effect/focusing.png");
	_effectImg[EffectType::rotation] = RRMLib::LoadGraph("Resource/img/Effect/rotation.png");
	_effectImg[EffectType::question] = RRMLib::LoadGraph("Resource/img/Effect/question.png");
	_effectImg[EffectType::exclamation] = RRMLib::LoadGraph("Resource/img/Effect/exclamation.png");
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
	case EffectType::rotation:
		return new GeneralEffect(_effectImg[EffectType::rotation], pos, 1792, 2304, 9, 7, 1.0f, size, isLoop);
		break;
	case EffectType::slash2:
		return new GeneralEffect(_effectImg[EffectType::slash2], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	case EffectType::focusing:
		return new GeneralEffect(_effectImg[EffectType::focusing], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	case EffectType::emergence:
		return new GeneralEffect(_effectImg[EffectType::emergence], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	case EffectType::defeat:
		return new GeneralEffect(_effectImg[EffectType::defeat], pos, 1792, 2048, 8, 7, 1.0f, size, isLoop);
		break;
	case EffectType::question:
		return new GeneralEffect(_effectImg[EffectType::question], pos, 1280, 1536, 6, 5, 1.0f, size, isLoop);
		break;
	case EffectType::exclamation:
		return new GeneralEffect(_effectImg[EffectType::exclamation], pos, 1280, 768, 3, 5, 1.0f, size, isLoop);
		break;
	default:
		return nullptr;
		break;
	}

	return nullptr;
}
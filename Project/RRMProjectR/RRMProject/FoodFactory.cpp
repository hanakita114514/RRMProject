#include "FoodFactory.h"
#include "GraphicLoad.h"
#include "GeneralFood.h"

FoodFactory::FoodFactory()
{
	GraphicLoad& gl = GraphicLoad::Instance();
	_handleMap[FoodType::banana] = gl.LoadGraph("Resource/img/Food/banana.png");
	_handleMap[FoodType::beaf] = gl.LoadGraph("Resource/img/Food/beaf.png");
	_handleMap[FoodType::bread] = gl.LoadGraph("Resource/img/Food/bread_yakisoba.png");
	_handleMap[FoodType::cake] = gl.LoadGraph("Resource/img/Food/cake.png");
	_handleMap[FoodType::chikuwa] = gl.LoadGraph("Resource/img/Food/chikuwa.png");
	_handleMap[FoodType::choko_corone] = gl.LoadGraph("Resource/img/Food/choko_corone.png");
	_handleMap[FoodType::corn] = gl.LoadGraph("Resource/img/Food/corn.png");
	_handleMap[FoodType::dashimaki] = gl.LoadGraph("Resource/img/Food/dashimaki.png");
	_handleMap[FoodType::donut] = gl.LoadGraph("Resource/img/Food/donut.png");
	_handleMap[FoodType::ketchup] = gl.LoadGraph("Resource/img/Food/ketchup.png");
	_handleMap[FoodType::kinoko] = gl.LoadGraph("Resource/img/Food/kinoko.png");
	_handleMap[FoodType::mayonnaise] = gl.LoadGraph("Resource/img/Food/mayonnaise.png");
	_handleMap[FoodType::meron_bread] = gl.LoadGraph("Resource/img/Food/meron_bread.png");
	_handleMap[FoodType::onigiri] = gl.LoadGraph("Resource/img/Food/onigiri_3.png");
	_handleMap[FoodType::pearch] = gl.LoadGraph("Resource/img/Food/pearch.png");
	_handleMap[FoodType::pepper] = gl.LoadGraph("Resource/img/Food/pepper.png");
	_handleMap[FoodType::salt] = gl.LoadGraph("Resource/img/Food/salt.png");
	_handleMap[FoodType::siitake] = gl.LoadGraph("Resource/img/Food/siitake.png");
	_handleMap[FoodType::tomato] = gl.LoadGraph("Resource/img/Food/tomato.png");
	_handleMap[FoodType::tori_karaage] = gl.LoadGraph("Resource/img/Food/tori_karaage_2.png");

}


FoodFactory::~FoodFactory()
{
}

Food* 
FoodFactory::Create(FoodType type, const Position& pos, const Vector2& vel, double turnAngle)
{
	Food::FoodStatus fs;
	fs.defense = 10;
	fs.pow = 10;
	fs.speed = 10;

	switch (type)
	{
	case FoodType::banana:
		return new GeneralFood(_handleMap[FoodType::banana], pos, vel, fs, turnAngle);
		break;
	case FoodType::beaf:
		return new GeneralFood(_handleMap[FoodType::beaf], pos, vel, fs, turnAngle);
		break;
	case FoodType::bread:
		return new GeneralFood(_handleMap[FoodType::bread], pos, vel, fs, turnAngle);
		break;
	case FoodType::cake:
		return new GeneralFood(_handleMap[FoodType::cake], pos, vel, fs, turnAngle);
		break;
	case FoodType::chikuwa:
		return new GeneralFood(_handleMap[FoodType::chikuwa], pos, vel, fs, turnAngle);
		break;
	case FoodType::choko_corone:
		return new GeneralFood(_handleMap[FoodType::choko_corone], pos, vel, fs, turnAngle);
		break;
	case FoodType::corn:
		return new GeneralFood(_handleMap[FoodType::corn], pos, vel, fs, turnAngle);
		break;
	case FoodType::dashimaki:
		return new GeneralFood(_handleMap[FoodType::dashimaki], pos, vel, fs, turnAngle);
		break;
	case FoodType::donut:
		return new GeneralFood(_handleMap[FoodType::donut], pos, vel, fs, turnAngle);
		break;
	case FoodType::ketchup:
		return new GeneralFood(_handleMap[FoodType::ketchup], pos, vel, fs, turnAngle);
		break;
	case FoodType::kinoko:
		return new GeneralFood(_handleMap[FoodType::kinoko], pos, vel, fs, turnAngle);
		break;
	case FoodType::mayonnaise:
		return new GeneralFood(_handleMap[FoodType::mayonnaise], pos, vel, fs, turnAngle);
		break;
	case FoodType::meron_bread:
		return new GeneralFood(_handleMap[FoodType::meron_bread], pos, vel, fs, turnAngle);
		break;
	case FoodType::onigiri:
		return new GeneralFood(_handleMap[FoodType::onigiri], pos, vel, fs, turnAngle);
		break;
	case FoodType::pearch:
		return new GeneralFood(_handleMap[FoodType::pearch], pos, vel, fs, turnAngle);
		break;
	case FoodType::pepper:
		return new GeneralFood(_handleMap[FoodType::pepper], pos, vel, fs, turnAngle);
		break;
	case FoodType::salt:
		return new GeneralFood(_handleMap[FoodType::salt], pos, vel, fs, turnAngle);
		break;
	case FoodType::siitake:
		return new GeneralFood(_handleMap[FoodType::siitake], pos, vel, fs, turnAngle);
		break;
	case FoodType::tomato:
		return new GeneralFood(_handleMap[FoodType::tomato], pos, vel, fs, turnAngle);
		break;
	case FoodType::tori_karaage:
		return new GeneralFood(_handleMap[FoodType::tori_karaage], pos, vel, fs, turnAngle);
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

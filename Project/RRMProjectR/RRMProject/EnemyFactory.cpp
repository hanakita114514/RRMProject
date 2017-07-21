#include "EnemyFactory.h"
#include "Egg.h"
#include "Mushroom.h"
#include"SushiMon.h"
#include <RRMLib.h>
#include "Meat.h"
#include "Hamburger.h"

EnemyFactory::EnemyFactory()
{
	_imgMap[EnemyType::egg] = RRMLib::LoadGraph("Resource/img/Enemy/tamatama.png");
	_imgMap[EnemyType::sushi] = RRMLib::LoadGraph("Resource/img/Enemy/eggDragon.png");
	_imgMap[EnemyType::mushroom] = RRMLib::LoadGraph("Resource/img/Enemy/mush.png");
	_imgMap[EnemyType::meat] = RRMLib::LoadGraph("Resource/img/Enemy/meatMon.png");
	_imgMap[EnemyType::hamburger] = RRMLib::LoadGraph("Resource/img/Enemy/kingBurger.png");
}


EnemyFactory::~EnemyFactory()
{
}

Enemy*
EnemyFactory::Create(const EnemyType& et, const Position& pos)
{
	switch (et)
	{
	case EnemyType::egg:
	{
		return new Egg(_imgMap[EnemyType::egg], pos);
	}
	break;
	case EnemyType::mushroom:
	{
		return new Mushroom(_imgMap[EnemyType::mushroom], pos);
	}
	break;
	case EnemyType::meat:
	{
		return new Meat(_imgMap[EnemyType::meat], pos);
	}
	break;
	case EnemyType::sushi:
	{
		return new SushiMon(_imgMap[EnemyType::sushi], pos);
	}
	break;
	case EnemyType::tomato:
	{

	}
	break;
	case EnemyType::hamburger:
	{
		return new Hamburger(_imgMap[EnemyType::hamburger], pos);
	}
	break;
	default:
		return nullptr;
		break;
	}

	return nullptr;
}
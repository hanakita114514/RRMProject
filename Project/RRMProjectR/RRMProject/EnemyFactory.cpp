#include "EnemyFactory.h"
#include "Egg.h"
#include "Mushroom.h"
#include "SushiMon.h"
#include "Meat.h"
#include <RRMLib.h>

EnemyFactory::EnemyFactory()
{
	_imgMap[EnemyType::egg] = RRMLib::LoadGraph("Resource/img/Enemy/tamatama.png");
	_imgMap[EnemyType::sushi] = RRMLib::LoadGraph("Resource/img/Enemy/eggDragon.png");
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

	}
	case EnemyType::sushi:
		return new SushiMon(_imgMap[EnemyType::sushi], pos);
		break;
	default:
		return nullptr;
		break;
	}

	return nullptr;
}
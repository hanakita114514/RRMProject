#include "EnemyFactory.h"
#include "Egg.h"
#include "Mushroom.h"
#include"SushiMon.h"
#include <RRMLib.h>

EnemyFactory::EnemyFactory()
{
	_imgMap[EnemyType::egg] = RRMLib::LoadGraph("Resource/img/Enemy/tamatama.png");
	_imgMap[EnemyType::sushi] = RRMLib::LoadGraph("Resource/img/Enemy/eggDragon.png");
	_imgMap[EnemyType::mushroom] = RRMLib::LoadGraph("Resource/img/Enemy/mush.png");
}


EnemyFactory::~EnemyFactory()
{
}

Enemy*
EnemyFactory::Create(const EnemyType& et, const Position& pos)
{

	Enemy* enemy = nullptr;
	switch (et)
	{
	case EnemyType::egg:
	{
		enemy = new Egg(_imgMap[EnemyType::egg], pos);
	}
		break;
	case EnemyType::mushroom:
	{
		enemy = new Egg(_imgMap[EnemyType::egg], pos);
	}
		break;
	case EnemyType::meat:
	{

	}
	break;
	case EnemyType::sushi:
	{
		enemy = new SushiMon(_imgMap[EnemyType::sushi], pos);
	}
	break;
	case EnemyType::tomato:
	{

	}
	break;
	case EnemyType::hamburger:
	{

	}
	break;
	default:
		break;
	}

	return enemy;
}
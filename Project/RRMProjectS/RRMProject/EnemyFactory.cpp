#include "EnemyFactory.h"
#include "Egg.h"
#include "Mushroom.h"
#include <RRMLib.h>

EnemyFactory::EnemyFactory()
{
	_eggImg[0] = RRMLib::LoadGraph("Resource/img/Enemy/Tamaran1.bmp");
	_eggImg[1] = RRMLib::LoadGraph("Resource/img/Enemy/Tamaran2.bmp");
	_eggImg[2] = RRMLib::LoadGraph("Resource/img/Enemy/Tamaran3.bmp");

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
		enemy = new Egg(_eggImg, pos);
	}
		break;
	case EnemyType::mushroom:
	{
		//enemy = new Mushroom();
	}
		break;
	default:
		break;
	}

	return enemy;
}
#include "BulletFactory.h"
#include "HomingBullet.h"
#include "NormalBullet.h"
#include "SinBullet.h"
#include <DxLib.h>
#include "Lazer.h"
#include "BezierBullet.h"
#include "DeffusionBullet.h"
#include "CircleBullet.h"

BulletFactory::BulletFactory()
{
	_handle = DxLib::LoadGraph("Resource/img/Bullet/bullet.png");
}


BulletFactory::~BulletFactory()
{

}

Bullet*
BulletFactory::Create(const BulletType& bulletID, Vector2 vec,ObjectType type,Vector2 entry)
{
	Bullet* newBullet = nullptr;

	switch (bulletID)
	{
	case BulletType::normal:
	{
		newBullet = new NormalBullet(_handle);
		newBullet->Initialize(vec, type);
		break;
	}
	case BulletType::homing:
	{
		newBullet = new HomingBullet(_handle,vec);
		newBullet->Initialize(vec, type);
		break;
	}
	case BulletType::sinBullet:
	{
		newBullet = new SinBullet(_handle);
		newBullet->Initialize(vec,type);
		break;
	}
	case BulletType::lazer:
	{
		newBullet = new Lazer();
		newBullet->Initialize(vec, type);
		break;
	}
	case BulletType::bezier:
	{
		newBullet = new BezierBullet(_handle,entry);
		newBullet->Initialize(vec, type);
		break;
	}
	case BulletType::deffusion:
	{
		newBullet = new DeffusionBullet(_handle);
		newBullet->Initialize(vec, type);
		break;
	}
	case BulletType::circleBullet:
	{
		newBullet = new CircleBullet(_handle);
		newBullet->Initialize(vec, type);
		break;
	}
	default:
		break;
	}

	return newBullet;
}

#include  <DxLib.h>
#include "BulletManager.h"
#include "GameMain.h"

BulletManager::BulletManager()
{
	_fac = new BulletFactory();
}


BulletManager::~BulletManager()
{
	free(_fac);
}

void BulletManager::Update()
{
		//====================================================================
		for (auto b : _fac->Getlist())
		{
			if (b->IsAlive())
			{
				b->Update();
			}
		}
		//=====================================================================
}

void BulletManager::Draw()
{
	for (auto b : _fac->Getlist())
	{
		if (b->IsAlive())
		{
			b->Draw();
		}
	}
}


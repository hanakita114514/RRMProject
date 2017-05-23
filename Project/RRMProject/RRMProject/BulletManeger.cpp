#include  <DxLib.h>
#include "BulletManeger.h"
#include "GameMain.h"

BulletManeger::BulletManeger()
{
	_fac = new BulletFactory();
}


BulletManeger::~BulletManeger()
{
	free(_fac);
}

void BulletManeger::Update()
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

void BulletManeger::Draw()
{
	for (auto b : _fac->Getlist())
	{
		if (b->IsAlive())
		{
			b->Draw();
		}
	}
}


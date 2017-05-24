#include "Lazer.h"
#include <DxLib.h>
#include "BulletFactory.h"
#include "BulletManeger.h"
#include "GameMain.h"
#include "GameTime.h"

const float RAD = 3.14f / 2.0f;
const float REDUCE_LIFE = 1.0f;

Lazer::Lazer()
{
	DxLib::LoadDivGraph("Resource/img/lazer.png", IMAGE_MAX, IMAGE_MAX, 1, IMAGE_SIZE_X, IMAGE_SIZE_Y, _handle);
}


Lazer::~Lazer()
{

}

void Lazer::Initialize(Vector2 vec, ObjectType type)
{
	_isAlive = true;
	_vel = Vector2(5.0, 0);
	_vel.x = _vel.x *vec.x;
	_vec = vec;
	_life = 150.0f;
	_objType = type;
}

void Lazer::Initialize()
{

}

void Lazer::Update()
{

	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();

	if (_life == 0)
	{
		_isAlive = false;
	}
	_circle.pos += _vel * GameTime::Instance().GetTimeScale();
}


void Lazer::Draw()
{
	DrawRotaGraph(_circle.pos.x, _circle.pos.y, 1,RAD, _handle[0], true);
}

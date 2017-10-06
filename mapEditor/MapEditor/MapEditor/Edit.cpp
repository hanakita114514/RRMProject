#include "Edit.h"
#include <DxLib.h>
Edit::Edit()
{
}


Edit::~Edit()
{
}

void Edit::Init(float x, float y, float z)
{
	_size.x = x;
	_size.y = y;
	_size.z = z;
}

void Edit::Draw()
{
	DrawLine3D(VGet(0, 0, 0), VGet(320, 0, 0), 0xffffff);
	DrawLine3D(VGet(0, 0, 0), VGet(0, 480, 0), 0xffffff);
}

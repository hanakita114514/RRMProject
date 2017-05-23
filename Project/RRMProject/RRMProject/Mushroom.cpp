#include "Mushroom.h"
#include <DxLib.h>

Mushroom::Mushroom()
{
}


Mushroom::Mushroom(int handle)
{
	_handle = handle;
}

Mushroom::~Mushroom()
{
}

void Mushroom::Initialize()
{

}

void Mushroom::Update()
{

}

void Mushroom::Draw()
{
	DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle, true);
}

void Mushroom::Anim()
{

}

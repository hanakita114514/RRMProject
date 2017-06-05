#include "Meat.h"
#include <DxLib.h>

Meat::Meat()
{
}


Meat::Meat(int handle)
{
	_handle = handle;
}

Meat::~Meat()
{
}

void Meat::Initialize()
{

}

void Meat::Update()
{

}

void Meat::Draw()
{
	DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle, true);
}

void Meat::Anim()
{

}
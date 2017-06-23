#include "Mushroom.h"
#include <RRMLib.h>

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

void Mushroom::Draw(const Vector2& offset)
{
	RRMLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle);
}

void Mushroom::Anim()
{

}

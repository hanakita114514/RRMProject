#include "Meat.h"
#include <RRMLib.h>

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
	RRMLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle);
}

void Meat::Anim()
{

}
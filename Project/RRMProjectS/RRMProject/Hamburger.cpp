#include "Hamburger.h"
#include <RRMLib.h>

Hamburger::Hamburger()
{
}

Hamburger::Hamburger(int handle)
{
	_handle = handle;
}

Hamburger::~Hamburger()
{
}

void Hamburger::Initialize()
{

}

void Hamburger::Update()
{

}

void Hamburger::Draw()
{
	RRMLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle);
}

void Hamburger::Anim()
{

}
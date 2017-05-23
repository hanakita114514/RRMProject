#include "Hamburger.h"
#include <DxLib.h>

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
	DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle, true);
}

void Hamburger::Anim()
{

}
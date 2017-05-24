#include "Camera.h"



Camera::Camera()
{

}


Camera::~Camera()
{
}

void
Camera::Init()
{
	_offset = Vector2(0, 0);
}

void
Camera::Update()
{

}

void 
Camera::Quake()
{

}

Vector2& 
Camera::GetOffset()
{
	return _offset;
}
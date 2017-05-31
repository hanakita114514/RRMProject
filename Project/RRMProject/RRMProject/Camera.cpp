#include "Camera.h"
#include "common.h"
#include <cmath>

Camera::Camera(const Position& targetPos) : _targetPos(targetPos)
{
	Init();
}


Camera::~Camera()
{
}

void
Camera::Init()
{
	_offset = Vector2(0, 0);
	_quakeOffset = Vector2(0, 0);
	_quakeFrame = 0;

	//カメラの位置
	_rc.pos.x = 0;
	_rc.pos.y = 0;
	//カメラの取る範囲
	_rc.w = WINDOW_WIDTH;
	_rc.h = WINDOW_HEIGHT;

	//マップの大きさを渡す
	_mapRc.pos.x = 0;	//マップの始点
	_mapRc.pos.y = 0;
	//マップの終点
	_mapRc.w = WINDOW_WIDTH;
	_mapRc.h = WINDOW_HEIGHT;
}

void
Camera::Update()
{
	float offsetX;
	_rc.pos.x = _targetPos.x - _rc.w / 2;
	if (_rc.pos.x + _rc.w >= _mapRc.w)
	{
		offsetX = _rc.pos.x - ((_rc.pos.x + _rc.w) - _mapRc.w);
	}
	else
	{
		offsetX = _rc.pos.x;
	}

	offsetX = std::fmax(_mapRc.pos.x, std::fmin(_mapRc.pos.x + _mapRc.w / 2, offsetX));

	_offset.x = offsetX + _quakeOffset.x;


	float offsetY;
	_rc.pos.y = _targetPos.y - _rc.h / 2;
	if (_rc.pos.y + _rc.h >= _mapRc.h)
	{
		offsetY = _rc.pos.y - ((_rc.pos.y + _rc.h) - _mapRc.h);
	}
	else
	{
		offsetY = _rc.pos.y;
	}

	offsetY = std::fmax(_mapRc.pos.y, std::fmin(_mapRc.pos.y + _mapRc.h / 2, offsetY));
	_offset.y = offsetY + _quakeOffset.y;

	if (_quakeFrame > 0)
	{
		_quakeOffset.x = -_quakeOffset.x * 0.9f;
		_quakeOffset.y = -_quakeOffset.y * 0.9f;
		--_quakeFrame;
	}
	else
	{
		_quakeOffset = Vector2(0, 0);
		_quakeFrame = 0;
	}
}

void 
Camera::Quake(const Vector2& power)
{
	_quakeFrame = 60;
	_quakeOffset = power;
}

const Vector2& 
Camera::GetOffset()
{
	return _offset;
}

const Rect& 
Camera::GetMapSize()
{
	return _mapRc;
}
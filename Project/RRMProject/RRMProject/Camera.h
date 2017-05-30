#pragma once

#include "Vector2.h"
#include "Rect.h"

//画面移動、揺らしなどを行う。
class Camera
{
private:
	Vector2 _offset;
	Vector2 _quakeOffset;
	int _quakeFrame;

	Rect _rc;
	Rect _mapRc;

	const Position& _targetPos;

public:
	Camera(const Position& targetPos);
	~Camera();

	void Init();
	void Update();
	void Quake(const Vector2& power);

	const Vector2& GetOffset();
	//マップの大きさを返す
	const Rect& GetMapSize();

};


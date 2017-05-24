#pragma once

#include "Vector2.h"
#include "Rect.h"

//‰æ–ÊˆÚ“®A—h‚ç‚µ‚È‚Ç‚ğs‚¤B
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

};


#pragma once
#include "Vector2.h"

class Mouse
{
private:
	Vector2 _pos;
	int _prevHistory;
	int _now;
public:
	Mouse();
	~Mouse();

	void Update();
	void Draw(float x,float y,unsigned int col = 0xffffffff);
	bool IsPressLeft();
	bool IsReleseLeft();
	bool IsPressRight();
	bool IsReleseRight();
	bool IsPressMiddle();
	bool IsReleseMiddle();
	Vector2 GetPos() { return _pos; }
};


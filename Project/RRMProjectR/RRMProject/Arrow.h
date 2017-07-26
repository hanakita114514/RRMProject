#pragma once
#include "UI.h"

const int ArrowWidth = 32;
const int ArrowHeight = 32;

class Arrow : public UI
{
	int _arrowHandle;
	float _width;
	float _height;
public:
	Arrow();
	Arrow(const Vector2& pos);
	~Arrow();

	void Draw();

	void Move(Vector2 velocity);

	void SetPos(Position position);
};


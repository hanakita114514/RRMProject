#pragma once
#include "UI.h"

const int ArrowWidth = 64;
const int ArrowHeight = 52;

class Arrow : public UI
{
	int _arrowHandle;
	float _width;
	float _height;
public:
	Arrow();
	~Arrow();

	void Draw();

	void SetPos(Position position);
};


#pragma once

#include "Vector2.h"
#include "HitPoint.h"

class HPBar
{
private:
	int _barHandle;
	int _gaugeHandle;

	Position _barPos;
public:
	HPBar();
	~HPBar();

	void Draw(Position ownPos, HitPoint hp);
};


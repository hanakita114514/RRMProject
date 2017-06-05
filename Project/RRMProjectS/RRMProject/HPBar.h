#pragma once

#include "Vector2.h"
#include "HitPoint.h"

class HPBar
{
private:
	int _barHandle;
	int _gaugeHandle;

public:
	HPBar();
	~HPBar();

	void Draw(const Position& pos, HitPoint& hp);
};


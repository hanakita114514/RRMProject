#pragma once

#include "HitPoint.h"
#include "Vector2.h"

class PlayerHP
{
private:
	int _hpBarHandle;
	int _gaugeHandle;

	Position _barPos;

public:
	PlayerHP();
	~PlayerHP();

	void Draw(HitPoint& hp);
};


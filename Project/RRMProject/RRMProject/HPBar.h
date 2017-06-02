#pragma once

#include "Vector2.h"
#include "HitPoint.h"
#include "UI.h"

class HPBar : public UI
{
private:
	int _barHandle;
	int _gaugeHandle;

	const Position& _ownPos;
	HitPoint& _hp;

	Position _barPos;
public:
	HPBar(const Position& ownPos, HitPoint& hp);
	~HPBar();

	void Draw();
};


#pragma once

#include "HitPoint.h"
#include "Vector2.h"

class PlayerHP
{
private:
	static const int GAUGE_NUM = 3;
	int _hpBarHandle;
	int _gaugeHandle[GAUGE_NUM];

	Position _barPos;

	float _offset;
	float _backOffset;
	float _offsetBuf;

public:
	PlayerHP();
	~PlayerHP();

	void Update();
	void Commit();
	void Draw(HitPoint& hp);
};


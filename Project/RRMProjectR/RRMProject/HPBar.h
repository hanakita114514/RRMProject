#pragma once

#include "Vector2.h"
#include "HitPoint.h"

class HPBar
{
private:
	static const int GAUGE_NUM = 3;
	int _barHandle;
	int _gaugeHandle[GAUGE_NUM];

	float _offset;
	float _backOffset;
	float _offsetBuf;

public:
	HPBar();
	~HPBar();

	void Update();
	void Draw(const Position& pos, HitPoint& hp);
	void Commit();
};


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

	bool _isCommit;		//コミット中か？
	bool _isDone;

	int _commitFrame;
public:
	HPBar();
	~HPBar();

	void Update();
	void Draw(const Position& pos, HitPoint& hp);
	void Commit();
	void CommitPeriod();
};


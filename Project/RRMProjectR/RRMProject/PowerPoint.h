#pragma once

#include "Timer.h"

class PowerPoint
{
private:
	int _pp;
	int _maxPP;

	int _recVal;	//回復数

	Timer _time;

public:
	PowerPoint(int pp);
	~PowerPoint();

	void Update();		//毎フレーム呼ぶ

	bool Use();			//使用可能ならtrue

	int GetPowerPoint();
	int GetMaxPP();

	void SetMaxPP(const int& maxpp);

	//PPが最大か？
	bool IsPPMax();
	//PPが使えない状態か？
	bool IsAbsentPP();

	
};


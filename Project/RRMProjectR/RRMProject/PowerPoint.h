#pragma once

#include "Timer.h"

class PowerPoint
{
private:
	int _pp;
	int _maxPP;

	int _recVal;	//�񕜐�

	Timer _time;

public:
	PowerPoint(int pp);
	~PowerPoint();

	void Update();		//���t���[���Ă�

	bool Use();			//�g�p�\�Ȃ�true

	int GetPowerPoint();
	int GetMaxPP();

	void SetMaxPP(const int& maxpp);

	//PP���ő傩�H
	bool IsPPMax();
	//PP���g���Ȃ���Ԃ��H
	bool IsAbsentPP();

	
};


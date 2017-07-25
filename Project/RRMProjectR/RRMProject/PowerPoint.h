#pragma once

#include "Timer.h"
#include "Vector2.h"

class PowerPoint
{
private:
	int _pp;
	int _maxPP;

	int _recVal;	//�񕜐�

	Timer _time;

	int _handle;

	Position _pos;

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

	void Draw();
};
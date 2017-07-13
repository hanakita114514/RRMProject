#pragma once

#include "Number.h"

class Combo
{
private:
	int _comboTime;		//�R���{�̌q����͈�
	int _comboNum;		//�R���{��

	Number _number;

	//�摜�n���h��
	int _timeHandle;
	int _comboHandle;
	int _maxCombo;

	Position _pos;

	int _count;

public:
	Combo();
	~Combo();

	void Update();
	void Draw();
	void Hit();

	//�R���{���s
	void Failure();

	int GetComboNum() { return _comboNum; }
	int GetMaxCombo() { return _maxCombo; }
};


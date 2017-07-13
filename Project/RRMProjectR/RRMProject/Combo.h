#pragma once

#include "Number.h"

class Combo
{
private:
	int _comboTime;		//コンボの繋がる範囲
	int _comboNum;		//コンボ数

	Number _number;

	//画像ハンドル
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

	//コンボ失敗
	void Failure();

	int GetComboNum() { return _comboNum; }
	int GetMaxCombo() { return _maxCombo; }
};


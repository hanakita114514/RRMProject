#pragma once

#include "Vector2.h"

//キャラのステータスを表示する
class StatusUI
{
private:
	static const int FILTER_NUM = 2;
	int _handle;
	int _filterHandle[FILTER_NUM];

	Position _filterPos;
public:
	StatusUI();
	~StatusUI();

	void Draw();
};


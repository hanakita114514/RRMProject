#pragma once

#include "Vector2.h"

//�L�����̃X�e�[�^�X��\������
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


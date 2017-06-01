#pragma once

#include "Vector2.h"
//�G�t�F�N�g�̋K��N���X
class Effect
{
protected:
	int _handle;
	float _frame;

	Position _pos;		//���݈ʒu

	bool _deleteFlag;	//�I���ɂȂ��������
public:
	Effect();
	~Effect();

	virtual void Update() = 0;
	virtual void Draw(const Vector2& offset) = 0;

	bool IsDelete() { return _deleteFlag; }
};


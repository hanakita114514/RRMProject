#pragma once

#include "Vector2.h"
//エフェクトの規定クラス
class Effect
{
protected:
	int _handle;
	float _frame;
	Position _pos;		//現在位置
	Vector2 _uv;
	//画像サイズ
	Vector2 _size;
	bool _deleteFlag;	//オンになったら消す
public:
	Effect();
	~Effect();

	virtual void Update() = 0;
	virtual void Draw(const Vector2& offset) = 0;

	bool IsDelete() { return _deleteFlag; }
};


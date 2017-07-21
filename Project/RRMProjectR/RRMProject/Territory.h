#pragma once
#include "Rect.h"
#include "Vector2.h"


//Terrytoryクラス
//敵の移動範囲とかを設定するクラス
class Territory
{
private:
	Rect _range;			//領域の範囲
	bool _outRange;			//領域外に出たかどうか
public:
	Territory();
	~Territory();

	void Update(const Rect& rc);

	void Set(float xRange, float yRange, Vector2 pos);

	//領域の範囲外に出たか？
	bool IsOutRange() { return _outRange; }

	//移動方向を反転したときに使ってください
	void InRange() { _outRange = false; }
};


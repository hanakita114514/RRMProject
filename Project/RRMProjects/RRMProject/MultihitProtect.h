#pragma once

#include "Object.h"
#include <map>

//当たり判定の多段ヒットを防ぐクラス
class MultihitProtect
{
private:
	std::map <Object*, bool> _hitMap;

public:
	MultihitProtect();
	~MultihitProtect();

	//すでに当たっているか？
	bool IsAlreadyHit(Object* other) { return _hitMap[other]; }
	//当たった時に呼ぶ
	void Hit(Object* other);
	
	//当たった履歴を消す
	void Clear();
};


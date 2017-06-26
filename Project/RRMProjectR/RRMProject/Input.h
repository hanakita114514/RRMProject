#pragma once
#include "Vector2.h"

class Input
{
protected:

public:
	Input();
	~Input();

	////操作関連　押されている時 true
	////移動
	//virtual bool Left();
	//virtual bool Right();
	//virtual bool Up();
	//virtual bool Down();

	////ニュートラル
	//virtual bool Neautral();

	////R,Lトリガー処理
	//virtual bool LeftTriger();
	//virtual bool RightTriger();

	////急降下
	//virtual bool Nosedive();

	////攻撃
	//virtual bool Shoot();		//遠距離攻撃
	//virtual bool Attack();		//通常攻撃
	//virtual bool Jump();
	//virtual bool Digestion();	//消化

	//virtual bool Avoidance();	//回避
	//virtual bool Parry();		//パリィ

	//virtual bool WeaponSwitch();	//武器切り替え
	//virtual bool ToolSwitch();		//飛び道具切り替え

	//virtual bool Start();			//スタートボタン
	//virtual bool Select();			//セレクトボタン

	//virtual Vector2& Dir();			//向きを返す
};


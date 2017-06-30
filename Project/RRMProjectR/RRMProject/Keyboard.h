#pragma once
#include <map>
#include "Vector2.h"
#include "Input.h"

//キーボード操作
class Keyboard : public Input
{
private:
	static const int keyNum = 256;
	char _key[keyNum];
	char _keyHistory[keyNum];

	std::map<KeyType, int> _keyType;
	std::map<KeyType, int> _repFrame;

	Vector2 _vec;

public:
	Keyboard();
	~Keyboard();

	void Update();
	//ボタンを押したとき
	bool IsTriger(const KeyType& inputType);
	//ボタンを押している間
	bool IsPress(const KeyType& inputType);
	//ボタンを離したとき
	bool IsRelease(const KeyType& inputType);
	//ボタンのリピート
	bool IsRepeat(const KeyType& inputType);

	void KeySwap(const KeyType& key1, const KeyType& key2);

	//操作関連　押されている時 true
	//移動
	bool Left();
	bool Right();
	bool Up();
	bool Down();

	//ニュートラル
	bool Neautral();

	//R,Lトリガー処理
	bool LeftTriger();
	bool RightTriger();

	//急降下
	bool Nosedive();

	//攻撃
	bool Shoot();		//遠距離攻撃
	bool Attack();		//通常攻撃
	bool Jump();
	bool Digestion();	//消化

	bool Avoidance();	//回避
	bool Parry();		//パリィ

	bool WeaponSwitch();	//武器切り替え
	bool ToolSwitch();		//飛び道具切り替え

	bool Start();			//スタートボタン
	bool Select();			//セレクトボタン

	Vector2& Dir();			//向きを返す
};


#pragma once

#include <RRMLib.h>
#include "Vector2.h"
#include <map>
#include "Input.h"

const int HISTORY_NUM = 64;

enum TrigerType
{
	leftTriger,
	rightTriger,
	trigerMax
};

enum class StickType
{
	up,
	down,
	left,
	right,
	max
};


class DInput : public Input
{
private:
	RRMLib::DJOYPAD_STATE _pad;
	RRMLib::DJOYPAD_STATE _history[HISTORY_NUM];
	bool _prevTriger[trigerMax],_triger[trigerMax];

	std::map<KeyType, unsigned int> _keyType;

	int _padType;
	unsigned char GetKey(const unsigned char* pad, const KeyType& key);

	std::map<KeyType, int> _repFrame;

	bool _prevStick[(int)StickType::max];
	bool _stick[(int)StickType::max];
public:
	DInput(int padType);	//パッドの番号を1～4で指定
	~DInput();

	void Update();
	
	//ボタンを押したとき
	bool IsTriger(const KeyType& keyType);
	//ボタンを押している間
	bool IsPress(const KeyType& keyType);
	//ボタンを離したとき
	bool IsRelease(const KeyType& keyType);
	//ボタンのリピート
	bool IsRepeat(const KeyType& keyType, int repCnt);


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
	bool Shoot(int repCnt);	//遠距離攻撃

	bool Attack();		//通常攻撃
	bool UpAttack();
	bool DownAttack();

	bool Jump();
	bool Digestion();	//消化

	bool Avoidance();	//回避
	bool Parry();		//パリィ

	bool WeaponSwitch();	//武器切り替え
	bool ToolSwitch();		//飛び道具切り替え

	bool Start();			//スタートボタン
	bool Select();			//セレクトボタン

	Vector2& Dir();			//向きを返す

	bool RightStickTriger();
	bool LeftStickTriger();
	bool UpStickTriger();
	bool DownStickTriger();

	bool Decision();
	bool Exit();
};


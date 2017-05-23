#pragma once

#include <DxLib.h>

const int HISTORY_NUM = 64;

enum class KeyType : unsigned int 
{
	keyA,
	keyB,
	keyX,
	keyY,
	keyL,
	keyR,
	keyBack,
	keyStart,
	keyTumbLeft,
	keyTumbRight,
};


class DInput
{
private:
	DINPUT_JOYSTATE _pad;
	DINPUT_JOYSTATE _history[HISTORY_NUM];

	int _padType;
	unsigned char GetKey(const unsigned char* pad, const KeyType& key);


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
	bool IsRepeat(const KeyType& keyType);


	//操作関連　押されている時 true
	//移動
	bool Left();
	bool Right();
	bool Up();
	bool Down();

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
};


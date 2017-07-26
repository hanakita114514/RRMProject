#pragma once
#include "Vector2.h"

const unsigned int rep_interval = 15;

enum class InputMode
{
	pad,
	keyboard,
};

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
	leftTriger,
	rightTriger,

	keyMax,
};

class Input
{
protected:

public:
	Input();
	~Input();

	virtual void Update() = 0;

	//ボタンを押したとき
	virtual bool IsTriger(const KeyType& keyType) = 0;
	//ボタンを押している間
	virtual bool IsPress(const KeyType& keyType) = 0;
	//ボタンを離したとき
	virtual bool IsRelease(const KeyType& keyType) = 0;
	//ボタンのリピート
	virtual bool IsRepeat(const KeyType& keyType, int repCnt) = 0;

	//操作関連　押されている時 true
	//移動
	virtual bool Left() = 0;
	virtual bool Right() = 0;
	virtual bool Up() = 0;
	virtual bool Down() = 0;

	//ニュートラル
	virtual bool Neautral() = 0;

	//R,Lトリガー処理
	virtual bool LeftTriger() = 0;
	virtual bool RightTriger() = 0;

	//急降下
	virtual bool Nosedive() = 0;

	//攻撃
	virtual bool Shoot(int repCnt) = 0;		//遠距離攻撃


	virtual bool Attack() = 0;
	virtual bool UpAttack() = 0; 		//通常攻撃
	virtual bool DownAttack() = 0;

	virtual bool Jump() = 0;
	virtual bool Digestion() = 0;	//消化

	virtual bool Avoidance() = 0;	//回避
	virtual bool Parry() = 0;		//パリィ

	virtual bool WeaponSwitch() = 0;	//武器切り替え
	virtual bool ToolSwitch() = 0;		//飛び道具切り替え

	virtual bool Start() = 0;			//スタートボタン
	virtual bool Select() = 0;			//セレクトボタン

	virtual Vector2& Dir() = 0;			//向きを返す

	virtual bool RightStickTriger() = 0;
	virtual bool LeftStickTriger() = 0;
	virtual bool UpStickTriger() = 0;
	virtual bool DownStickTriger() = 0;

	virtual bool Decision() = 0;		//決定
	virtual bool Exit() = 0;			//戻る
};


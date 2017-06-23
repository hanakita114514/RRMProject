#pragma once

#include <DxLib.h>


const int HISTORY_NUM = 256;

class XInput
{
private:
	XINPUT_STATE _xinput;
	XINPUT_STATE _history[HISTORY_NUM];	//キー履歴

	int _inputType;

public:
	// inputType パッドの番号を指定 1～4
	XInput(int inputType);
	~XInput();

	void Update();

	//ボタンを押したとき
	bool IsTriger(int keyType);
	//ボタンを押している間
	bool IsPress(int keyType);
	//ボタンを離したとき
	bool IsRelease(int keyType);
	//ボタンのリピート
	bool IsRepeat(int keyType);
};


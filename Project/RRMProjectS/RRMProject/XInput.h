#pragma once

#include <DxLib.h>


const int HISTORY_NUM = 256;

class XInput
{
private:
	XINPUT_STATE _xinput;
	XINPUT_STATE _history[HISTORY_NUM];	//�L�[����

	int _inputType;

public:
	// inputType �p�b�h�̔ԍ����w�� 1�`4
	XInput(int inputType);
	~XInput();

	void Update();

	//�{�^�����������Ƃ�
	bool IsTriger(int keyType);
	//�{�^���������Ă����
	bool IsPress(int keyType);
	//�{�^���𗣂����Ƃ�
	bool IsRelease(int keyType);
	//�{�^���̃��s�[�g
	bool IsRepeat(int keyType);
};


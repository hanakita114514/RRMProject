#pragma once

#include <DxLib.h>
#include "Vector2.h"
#include <map>

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

	std::map<KeyType, int> _repFrame;

public:
	DInput(int padType);	//�p�b�h�̔ԍ���1�`4�Ŏw��
	~DInput();

	void Update();
	
	//�{�^�����������Ƃ�
	bool IsTriger(const KeyType& keyType);
	//�{�^���������Ă����
	bool IsPress(const KeyType& keyType);
	//�{�^���𗣂����Ƃ�
	bool IsRelease(const KeyType& keyType);
	//�{�^���̃��s�[�g
	bool IsRepeat(const KeyType& keyType);


	//����֘A�@������Ă��鎞 true
	//�ړ�
	bool Left();
	bool Right();
	bool Up();
	bool Down();

	//�}�~��
	bool Nosedive();

	//�U��
	bool Shoot();		//�������U��
	bool Attack();		//�ʏ�U��
	bool Jump();
	bool Digestion();	//����

	bool Avoidance();	//���
	bool Parry();		//�p���B

	bool WeaponSwitch();	//����؂�ւ�
	bool ToolSwitch();		//��ѓ���؂�ւ�

	bool Start();			//�X�^�[�g�{�^��
	bool Select();			//�Z���N�g�{�^��

	Vector2& Dir();			//������Ԃ�
};

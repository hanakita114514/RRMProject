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
	bool IsRepeat(const KeyType& keyType, int repCnt);


	//����֘A�@������Ă��鎞 true
	//�ړ�
	bool Left();
	bool Right();
	bool Up();
	bool Down();

	//�j���[�g����
	bool Neautral();

	//R,L�g���K�[����
	bool LeftTriger();
	bool RightTriger();

	//�}�~��
	bool Nosedive();

	//�U��
	bool Shoot(int repCnt);	//�������U��

	bool Attack();		//�ʏ�U��
	bool UpAttack();
	bool DownAttack();

	bool Jump();
	bool Digestion();	//����

	bool Avoidance();	//���
	bool Parry();		//�p���B

	bool WeaponSwitch();	//����؂�ւ�
	bool ToolSwitch();		//��ѓ���؂�ւ�

	bool Start();			//�X�^�[�g�{�^��
	bool Select();			//�Z���N�g�{�^��

	Vector2& Dir();			//������Ԃ�

	bool RightStickTriger();
	bool LeftStickTriger();
	bool UpStickTriger();
	bool DownStickTriger();

	bool Decision();
	bool Exit();
};


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

	//�{�^�����������Ƃ�
	virtual bool IsTriger(const KeyType& keyType) = 0;
	//�{�^���������Ă����
	virtual bool IsPress(const KeyType& keyType) = 0;
	//�{�^���𗣂����Ƃ�
	virtual bool IsRelease(const KeyType& keyType) = 0;
	//�{�^���̃��s�[�g
	virtual bool IsRepeat(const KeyType& keyType, int repCnt) = 0;

	//����֘A�@������Ă��鎞 true
	//�ړ�
	virtual bool Left() = 0;
	virtual bool Right() = 0;
	virtual bool Up() = 0;
	virtual bool Down() = 0;

	//�j���[�g����
	virtual bool Neautral() = 0;

	//R,L�g���K�[����
	virtual bool LeftTriger() = 0;
	virtual bool RightTriger() = 0;

	//�}�~��
	virtual bool Nosedive() = 0;

	//�U��
	virtual bool Shoot(int repCnt) = 0;		//�������U��


	virtual bool Attack() = 0;
	virtual bool UpAttack() = 0; 		//�ʏ�U��
	virtual bool DownAttack() = 0;

	virtual bool Jump() = 0;
	virtual bool Digestion() = 0;	//����

	virtual bool Avoidance() = 0;	//���
	virtual bool Parry() = 0;		//�p���B

	virtual bool WeaponSwitch() = 0;	//����؂�ւ�
	virtual bool ToolSwitch() = 0;		//��ѓ���؂�ւ�

	virtual bool Start() = 0;			//�X�^�[�g�{�^��
	virtual bool Select() = 0;			//�Z���N�g�{�^��

	virtual Vector2& Dir() = 0;			//������Ԃ�

	virtual bool RightStickTriger() = 0;
	virtual bool LeftStickTriger() = 0;
	virtual bool UpStickTriger() = 0;
	virtual bool DownStickTriger() = 0;

	virtual bool Decision() = 0;		//����
	virtual bool Exit() = 0;			//�߂�
};


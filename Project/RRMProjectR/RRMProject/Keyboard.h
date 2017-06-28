#pragma once
#include <map>
#include "Vector2.h"
#include "Input.h"

//�L�[�{�[�h����
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
	//�{�^�����������Ƃ�
	bool IsTriger(const KeyType& inputType);
	//�{�^���������Ă����
	bool IsPress(const KeyType& inputType);
	//�{�^���𗣂����Ƃ�
	bool IsRelease(const KeyType& inputType);
	//�{�^���̃��s�[�g
	bool IsRepeat(const KeyType& inputType);

	void KeySwap(const KeyType& key1, const KeyType& key2);

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


#pragma once
#include <map>

enum class InputType : unsigned int 
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

	keyMax,
};

//�L�[�{�[�h����
class Keyboard
{
private:
	static const int keyNum = 256;
	char _key[keyNum];
	char _keyHistory[keyNum];

	std::map<InputType, int> _keyType;

public:
	Keyboard();
	~Keyboard();

	void Update();
	//�{�^�����������Ƃ�
	bool IsTriger(const InputType& inputType);
	//�{�^���������Ă����
	bool IsPress(const InputType& inputType);
	//�{�^���𗣂����Ƃ�
	bool IsRelease(const InputType& inputType);
	//�{�^���̃��s�[�g
	bool IsRepeat(const InputType& inputType);

	void KeySwap(const InputType& key1, const InputType& key2);
};


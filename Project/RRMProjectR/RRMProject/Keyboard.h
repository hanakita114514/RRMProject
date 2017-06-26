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

//キーボード操作
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
	//ボタンを押したとき
	bool IsTriger(const InputType& inputType);
	//ボタンを押している間
	bool IsPress(const InputType& inputType);
	//ボタンを離したとき
	bool IsRelease(const InputType& inputType);
	//ボタンのリピート
	bool IsRepeat(const InputType& inputType);

	void KeySwap(const InputType& key1, const InputType& key2);
};


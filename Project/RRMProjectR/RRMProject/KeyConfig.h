#pragma once
#include "Input.h"

struct KeyData
{
	InputMode mode;
};

//�L�[�R���t�B�O���Ǘ�����N���X
class KeyConfig
{
private:

public:
	KeyConfig();
	~KeyConfig();

	void Save(KeyData& keyData);
	void Load(KeyData& keyData);
};


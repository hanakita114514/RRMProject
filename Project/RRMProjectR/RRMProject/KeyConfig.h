#pragma once
#include "Input.h"

struct KeyData
{
	InputMode mode;
};

//キーコンフィグを管理するクラス
class KeyConfig
{
private:

public:
	KeyConfig();
	~KeyConfig();

	void Save(KeyData& keyData);
	void Load(KeyData& keyData);
};


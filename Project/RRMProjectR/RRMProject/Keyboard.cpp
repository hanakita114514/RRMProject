#include "Keyboard.h"
#include <RRMLib.h>


Keyboard::Keyboard()
{
	for (int i = 0; i < keyNum; i++)
	{
		_key[i] = 0;
		_keyHistory[i] = 0;
	}

	//キーを保存
	_keyType[KeyType::keyA] = KEY_Z;
	_keyType[KeyType::keyB] = KEY_X;
	_keyType[KeyType::keyX] = KEY_C;
	_keyType[KeyType::keyY] = KEY_V;
	_keyType[KeyType::keyL] = KEY_A;
	_keyType[KeyType::keyR] = KEY_S;
	_keyType[KeyType::keyStart] = KEY_RETURN;
	_keyType[KeyType::keyBack] = KEY_ESCAPE;
	_keyType[KeyType::rightTriger] = KEY_F;
	_keyType[KeyType::leftTriger] = KEY_D;

	_vec = Vector2(0, 0);

	for (int i = 0; i < (int)KeyboardDir::max; i++)
	{
		_prevState[i] = false;
		_nowState[i] = false;
	}
}


Keyboard::~Keyboard()
{
}

void
Keyboard::Update()
{
	for (int i = 0; i < keyNum; i++)
	{
		_keyHistory[i] = _key[i];
	}

	RRMLib::GetKeyboardState(_key);
}

//ボタンを押したとき
bool
Keyboard::IsTriger(const KeyType& inputType)
{
	if (_key[_keyType[inputType]] & ~_keyHistory[_keyType[inputType]])
	{
		return true;
	}
	return false;
}

//ボタンを押している間
bool
Keyboard::IsPress(const KeyType& inputType)
{
	if (_key[_keyType[inputType]])
	{
		return true;
	}
	return false;
}

//ボタンを離したとき
bool
Keyboard::IsRelease(const KeyType& inputType)
{
	if (~_key[_keyType[inputType]] & _keyHistory[_keyType[inputType]])
	{
		return true;
	}
	return false;
}

//ボタンのリピート
bool 
Keyboard::IsRepeat(const KeyType& inputType, int repCnt)
{
	if (IsPress(inputType))
	{
		_repFrame[inputType]++;
	}
	else
	{
		_repFrame[inputType] = 0;
	}

	if (_repFrame[inputType] > repCnt)
	{
		_repFrame[inputType] = 0;
		return true;
	}
	return false;
}

void 
Keyboard::KeySwap(const KeyType& key1, const KeyType& key2)
{
	int tmp = _keyType[key1];
	_keyType[key1] = _keyType[key2];
	_keyType[key2] = tmp;
}

bool 
Keyboard::Left()
{
	if (_key[KEY_LEFT])
	{
		_vec.x = -1;
		return true;
	}
	return false;
}

bool 
Keyboard::Right()
{
	if (_key[KEY_RIGHT])
	{
		_vec.x = 1;
		return true;
	}
	return false;
}

bool 
Keyboard::Up()
{
	if (_key[KEY_UP])
	{
		_vec.y = -1;
		return true;
	}
	return false;
}

bool 
Keyboard::Down()
{
	if (_key[KEY_DOWN])
	{
		_vec.y = 1;
		return true;
	}
	return false;

}

bool
Keyboard::Neautral()
{
	if (Left())
	{
		return false;
	}
	if (Right())
	{
		return false;
	}

	return true;
}

bool 
Keyboard::LeftTriger()
{
	return false;
}

bool 
Keyboard::RightTriger()
{
	return false;

}

bool 
Keyboard::Nosedive()
{
	return false;
}

bool 
Keyboard::Shoot(int repCnt)
{
	if (IsTriger(KeyType::keyA))
	{
		return true;
	}
	if (IsRepeat(KeyType::keyA, repCnt))	{
		return true;
	}

	return false;
}

bool 
Keyboard::Attack()
{
	if (IsTriger(KeyType::keyB))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::UpAttack()
{
	if (!Up())
	{
		return false;
	}
	if (!Attack())
	{
		return false;
	}

	return true;
}

bool 
Keyboard::Jump()
{
	if (IsTriger(KeyType::keyY))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Digestion()
{
	if (IsTriger(KeyType::keyX))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Avoidance()
{
	if (IsTriger(KeyType::keyR))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Parry()
{
	if (IsTriger(KeyType::keyL))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::WeaponSwitch()
{
	if (IsTriger(KeyType::rightTriger))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::ToolSwitch()
{
	if (IsTriger(KeyType::leftTriger))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Start()
{
	if (IsTriger(KeyType::keyStart))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Select()
{
	if (IsTriger(KeyType::keyBack))
	{
		return true;
	}
	return false;
}

Vector2&
Keyboard::Dir()
{
	_vec = Vector2(0, 0);
	Left();
	Right();
	Up();
	Down();

	return _vec;
}

bool 
Keyboard::RightStickTriger()
{
	_nowState[(int)KeyboardDir::right] = _prevState[(int)KeyboardDir::right];

	_nowState[(int)KeyboardDir::right] = Right();

	if (_nowState[(int)KeyboardDir::right] & (_nowState[(int)KeyboardDir::right] ^ _prevState[(int)KeyboardDir::right]))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::LeftStickTriger()
{
	_nowState[(int)KeyboardDir::left] = _prevState[(int)KeyboardDir::left];

	_nowState[(int)KeyboardDir::left] = Left();

	if (_nowState[(int)KeyboardDir::left] & (_nowState[(int)KeyboardDir::left] ^ _prevState[(int)KeyboardDir::left]))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::UpStickTriger()
{
	_nowState[(int)KeyboardDir::up] = _prevState[(int)KeyboardDir::up];

	_nowState[(int)KeyboardDir::up] = Up();

	if (_nowState[(int)KeyboardDir::up] & (_nowState[(int)KeyboardDir::up] ^ _prevState[(int)KeyboardDir::up]))
	{
		return true;
	}
	return false;
}

bool
Keyboard::DownStickTriger()
{
	_nowState[(int)KeyboardDir::down] = _prevState[(int)KeyboardDir::down];

	_nowState[(int)KeyboardDir::down] = Down();

	if (_nowState[(int)KeyboardDir::down] & (_nowState[(int)KeyboardDir::down] ^ _prevState[(int)KeyboardDir::down]))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Decision()
{
	if (IsTriger(KeyType::keyA))
	{
		return true;
	}
	return false;
}

bool 
Keyboard::Exit()
{
	if (IsTriger(KeyType::keyB))
	{
		return true;
	}
	return false;
}
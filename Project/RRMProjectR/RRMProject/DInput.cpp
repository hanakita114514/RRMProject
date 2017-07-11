#include "DInput.h"

const unsigned int PAD_UP = 0;
const unsigned int PAD_RIGHT_UP = 4500;
const unsigned int PAD_RIGHT = 9000;
const unsigned int PAD_RIGHT_DOWN = 13500;
const unsigned int PAD_DOWN = 18000;
const unsigned int PAD_LEFT_DOWN = 22500;
const unsigned int PAD_LEFT = 27000;
const unsigned int PAD_LEFT_UP = 31500;

const unsigned int PAD_MASK = 0x80;

const unsigned int PAD_A = 0;
const unsigned int PAD_B = 1;
const unsigned int PAD_X = 2;
const unsigned int PAD_Y = 3;
const unsigned int PAD_L = 4;
const unsigned int PAD_R = 5;
const unsigned int PAD_BACK = 6;
const unsigned int PAD_START = 7;
const unsigned int PAD_TUMB_LEFT = 8;
const unsigned int PAD_TUMB_RIGHT = 9;

DInput::DInput(int padType)
{
	_padType = padType;

	//int padNumber[4] =
	//{
	//	DX_INPUT_PAD1,
	//	DX_INPUT_PAD2,
	//	DX_INPUT_PAD3,
	//	DX_INPUT_PAD4,
	//};

	_padType = 0;

	RRMLib::DJOYPAD_STATE d = {};

	//ÉLÅ[óöóÇÃèâä˙âª
	for (int i = 0; i < HISTORY_NUM; i++)
	{
		_history[i] = d;
	}
	_pad = d;

	for (int i = 0; i < trigerMax; i++)
	{
		_triger[i] = false;
	}

	_keyType[KeyType::keyA]			= PAD_A;
	_keyType[KeyType::keyB]			= PAD_B;
	_keyType[KeyType::keyX]			= PAD_X;
	_keyType[KeyType::keyY]			= PAD_Y;
	_keyType[KeyType::keyL]			= PAD_L;
	_keyType[KeyType::keyR]			= PAD_R;
	_keyType[KeyType::keyBack]		= PAD_BACK;
	_keyType[KeyType::keyStart]		= PAD_START;
	_keyType[KeyType::keyTumbLeft]	= PAD_TUMB_LEFT;
	_keyType[KeyType::keyTumbRight] = PAD_TUMB_RIGHT;

}


DInput::~DInput()
{
}

unsigned char
DInput::GetKey(const unsigned char* pad, const KeyType& key)
{
	//return pad[static_cast<unsigned int>(key)] & PAD_MASK;
	return pad[_keyType[key]] & PAD_MASK;
}

void
DInput::Update()
{
	//óöóÇÇ∆Ç¡ÇƒÇ¢Ç≠
	for (int i = HISTORY_NUM - 1; i > 0; i--)
	{
		_history[i] = _history[i - 1];
	}

	_history[0] = _pad;
	GetJoypadDirectInputState(_padType, &_pad);

	for (int i = 0; i < trigerMax; i++)
	{
		_prevTriger[i] = _triger[i];
	}
}


bool
DInput::IsTriger(const KeyType& keyType)
{
	if (GetKey(_pad.buttons, keyType) & ~GetKey(_history[0].buttons, keyType))
	{
		return true;;
	}
	return false;
}

//bool
//DInput::IsPress(const KeyType& keyType)
//{
//	if (_pad.Buttons[static_cast<unsigned int>(keyType)] & PAD_MASK)
//	{
//		return true;
//	}
//	return false;
//}

bool 
DInput::IsPress(const KeyType& keyType)
{
	if (GetKey(_pad.buttons, keyType))
	{
		return true;
	}
	return false;
}

bool 
DInput::IsRelease(const KeyType& keyType)
{
	if (~GetKey(_pad.buttons, keyType) & GetKey(_history[0].buttons, keyType))
	{
		return true;;
	}
	return false;
}

bool 
DInput::IsRepeat(const KeyType& keyType, int repCnt)
{
	if (IsPress(keyType))
	{
		_repFrame[keyType]++;
	}
	else
	{
		_repFrame[keyType] = 0;
	}

	if (_repFrame[keyType] > repCnt)
	{
		_repFrame[keyType] = 0;
		return true;
	}

	return false;
}

bool 
DInput::Left()
{
	if (_pad.x < 0)
	{
		return true;
	}
	return false;
}

bool 
DInput::Right()
{
	if (_pad.x > 0)
	{
		return true;
	}
	return false;
}

bool 
DInput::Up()
{
	if (_pad.y < 0)
	{
		return true;
	}
	return false;
}

bool 
DInput::Down()
{
	if (_pad.y > 0)
	{
		return true;
	}

	return false;

}

bool
DInput::LeftTriger()
{
	if (_pad.z > 500)
	{
		return true;
	}
	return false;
}

bool
DInput::RightTriger()
{
	if (_pad.z < -500)
	{
		return true;
	}
	return false;
}

bool 
DInput::Neautral()
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
DInput::Nosedive()
{
	if (_pad.y - _history[0].y > 300)
	{
		if (_pad.y > 600)
		{
			return true;
		}
	}

	return false;
}

bool 
DInput::Shoot(int repCnt)
{
	if (IsTriger(KeyType::keyA))
	{
		return true;
	}
	if (IsRepeat(KeyType::keyA, repCnt))
	{
		return true;
	}
	return false;
}

bool 
DInput::Attack()
{
	if (IsTriger(KeyType::keyB))
	{
		return true;
	}
	return false;

}

bool 
DInput::UpAttack()
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
DInput::Jump()
{
	if (IsPress(KeyType::keyY))
	{
		return true;
	}
	return false;

}

bool 
DInput::Digestion()
{
	if (IsTriger(KeyType::keyX))
	{
		return true;
	}
	return false;
}

bool 
DInput::Avoidance()
{
	if (IsTriger(KeyType::keyR))
	{
		return true;
	}
	return false;
}

bool 
DInput::Parry()
{
	if (IsTriger(KeyType::keyL))
	{
		return true;
	}
	return false;

}

bool 
DInput::WeaponSwitch()
{
	_triger[rightTriger] = RightTriger();

	if (_triger[rightTriger] & (_triger[rightTriger] ^ _prevTriger[rightTriger]))
	{
		return true;
	}
	return false;
}

bool 
DInput::ToolSwitch()
{
	_triger[leftTriger] = LeftTriger();

	if (_triger[leftTriger] & (_triger[leftTriger] ^ _prevTriger[leftTriger]))
	{
		return true;
	}

	return false;

}

bool
DInput::Select()
{
	if (IsTriger(KeyType::keyBack))
	{
		return true;
	}
	return false;
}

bool
DInput::Start()
{
	if (IsTriger(KeyType::keyStart))
	{
		return true;
	}

	return false;
}

Vector2&
DInput::Dir()
{
	Vector2 v;
	v.x = _pad.x / 1000.0f;
	v.y = _pad.y / 1000.0f;
	return v;
}

bool
DInput::RightStickTriger()
{
	_prevStick[(int)StickType::right] = _stick[(int)StickType::right];
	_stick[(int)StickType::right] = Right();
	if (_stick[(int)StickType::right] & (_stick[(int)StickType::right] ^ _prevStick[(int)StickType::right]))
	{
		return true;
	}
	return false;
}

bool
DInput::LeftStickTriger()
{
	_prevStick[(int)StickType::left] = _stick[(int)StickType::left];
	_stick[(int)StickType::left] = Left();
	if (_stick[(int)StickType::left] & (_stick[(int)StickType::left] ^ _prevStick[(int)StickType::left]))
	{
		return true;
	}
	return false;

}

bool
DInput::UpStickTriger()
{
	_prevStick[(int)StickType::up] = _stick[(int)StickType::up];
	_stick[(int)StickType::up] = Up();
	if (_stick[(int)StickType::up] & (_stick[(int)StickType::up] ^ _prevStick[(int)StickType::up]))
	{
		return true;
	}
	return false;

}

bool
DInput::DownStickTriger()
{
	_prevStick[(int)StickType::down] = _stick[(int)StickType::down];
	_stick[(int)StickType::down] = Down();
	if (_stick[(int)StickType::down] & (_stick[(int)StickType::down] ^ _prevStick[(int)StickType::down]))
	{
		return true;
	}
	return false;

}

bool 
DInput::Decision()
{
	if (IsTriger(KeyType::keyB))
	{
		return true;
	}

	return false;
}

bool 
DInput::Exit()
{
	if (IsTriger(KeyType::keyA))
	{
		return true;
	}
	return false;
}
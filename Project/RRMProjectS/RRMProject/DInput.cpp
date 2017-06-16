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

const unsigned int rep_interval = 15;

DInput::DInput(int padType)
{
	_padType = padType;

	int padNumber[4] =
	{
		DX_INPUT_PAD1,
		DX_INPUT_PAD2,
		DX_INPUT_PAD3,
		DX_INPUT_PAD4,
	};

	_padType = padNumber[padType];

	DINPUT_JOYSTATE d = {};

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
}


DInput::~DInput()
{
}

unsigned char
DInput::GetKey(const unsigned char* pad, const KeyType& key)
{
	return pad[static_cast<unsigned int>(key)] & PAD_MASK;
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
	if (GetKey(_pad.Buttons, keyType) & ~GetKey(_history[0].Buttons, keyType))
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
	if (GetKey(_pad.Buttons, keyType))
	{
		return true;
	}
	return false;
}

bool 
DInput::IsRelease(const KeyType& keyType)
{
	if (~GetKey(_pad.Buttons, keyType) & GetKey(_history[0].Buttons, keyType))
	{
		return true;;
	}
	return false;
}

bool 
DInput::IsRepeat(const KeyType& keyType)
{
	if (IsPress(keyType))
	{
		_repFrame[keyType]++;
	}
	else
	{
		_repFrame[keyType] = 0;
	}

	if (_repFrame[keyType] > rep_interval)
	{
		_repFrame[keyType] = 0;
		return true;
	}

	return false;
}

bool 
DInput::Left()
{
	if (_pad.X < 0)
	{
		return true;
	}
	return false;
}

bool 
DInput::Right()
{
	if (_pad.X > 0)
	{
		return true;
	}
	return false;
}

bool 
DInput::Up()
{
	if (_pad.Y < 0)
	{
		return true;
	}
	return false;
}

bool 
DInput::Down()
{
	if (_pad.Y > 0)
	{
		return true;
	}

	return false;

}

bool
DInput::LeftTriger()
{
	if (_pad.Z > 500)
	{
		return true;
	}
	return false;
}

bool
DInput::RightTriger()
{
	if (_pad.Z < -500)
	{
		return true;
	}
	return false;
}

bool 
DInput::Nosedive()
{
	if (_pad.Y - _history[0].Y > 300)
	{
		if (_pad.Y > 600)
		{
			return true;
		}
	}

	return false;
}

bool 
DInput::Shoot()
{
	if (IsTriger(KeyType::keyA))
	{
		return true;
	}
	if (IsRepeat(KeyType::keyA))
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
	v.x = _pad.X / 1000.0f;
	v.y = _pad.Y / 1000.0f;
	return v;
}
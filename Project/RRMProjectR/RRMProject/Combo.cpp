#include "Combo.h"
#include <RRMLib.h>
#include <math.h>
#include "Mathematics.h"

static const float GAUGE_H = 10;
static const float GAUGE_OFFSET = 32.0f;

static const float COMBO_W = 128.0f;
static const float COMBO_H = 64.0f;

static const float NUM_FONT_SIZE = 64.0f;
static const float COMBO_OFFSET = NUM_FONT_SIZE + 10.0f;

Combo::Combo() :  _number(NUM_FONT_SIZE, RRMLib::LoadGraph("Resource/img/UI/Number/highScore/number1.png"), 64.0f, 64.0f)
{
	_comboTime = 0;
	_comboNum = 0;

	_timeHandle = RRMLib::LoadGraph("Resource/img/UI/comboTime.png");
	_comboHandle = RRMLib::LoadGraph("Resource/img/UI/combo.png");

	_pos = Position(100, 100);

	_count = 0;

	_maxCombo = 0;
}


Combo::~Combo()
{
}

void 
Combo::Update()
{
	--_comboTime;

	if (_comboTime <= 0)
	{
		this->Failure();
	}

	if (_maxCombo < _comboNum)
	{
		_maxCombo = _comboNum;
	}
}

void 
Combo::Draw()
{
	if (_comboTime > 0)
	{
		if (_comboNum >= 10)
		{
			float size = sin(PI * 2 / 60 * _count) * 30;
			++_count;
			_number.Draw(_comboNum, _pos,Vector2(size, size));
		}
		else
		{
			_number.Draw(_comboNum, _pos);
		}

		RRMLib::DrawExtendGraph(_pos.x, _pos.y + GAUGE_OFFSET, _pos.x + _comboTime, _pos.y + GAUGE_H + GAUGE_OFFSET, _timeHandle);
		
		Position _comboPos = Position(_pos.x + COMBO_OFFSET, _pos.y);
		RRMLib::DrawExtendGraph(_comboPos.x - COMBO_W / 2, _comboPos.y - COMBO_H / 2, _comboPos.x + COMBO_W / 2, _comboPos.y + COMBO_H / 2, _comboHandle);
	}
}

void 
Combo::Hit()
{
	++_comboNum;
	_comboTime = 60;
}

void 
Combo::Failure()
{
	_comboNum = 0;
	_comboTime = 0;
}
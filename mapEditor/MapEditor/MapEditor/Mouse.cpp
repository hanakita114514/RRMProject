#include "Mouse.h"
#include <DxLib.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Mouse::Mouse()
{
	_prevHistory = 0;
	_now = 0;
}


Mouse::~Mouse()
{
}

void Mouse::Update()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	_prevHistory = _now;
	_now = 0;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//ç∂Ç™âüÇ≥ÇÍÇΩ
		_now = 1;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		//âEÇ™âüÇ≥ÇÍÇΩ
		_now = 2;
	}
	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
	{
		_now = 4;
	}
	/*if (mouseX < 0)
	{
		mouseX = 0;
	}
	if (mouseX > WINDOW_WIDTH)
	{
		mouseX = WINDOW_WIDTH;
	}
	if (mouseY < 0)
	{
		mouseY = 0;
	}
	if (mouseY > WINDOW_HEIGHT)
	{
		mouseY = WINDOW_HEIGHT;
	}
	SetMousePoint(mouseX, mouseY);*/
	_pos.x = mouseX;
	_pos.y = mouseY;
	//DrawFormatString(0, 0, 0xffffffff, "%d", GetMouseInput() & MOUSE_INPUT_LEFT);
}

void Mouse::Draw(float x, float y, unsigned int col)
{
	DrawFormatString(x, y, col, "%d   %d", (int)_pos.x, (int)_pos.y);
	if (_now == 1)
	{
		DrawFormatString(x, y + 50, col, "ç∂");
	}

	if (_now == 2)
	{
		DrawFormatString(x + 50, y + 50, col, "âE");
	}


}

bool Mouse::IsPressLeft()
{
	
	return ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0);
}

bool Mouse::IsReleseLeft()
{
	return (_prevHistory == 1 && _now == 0);
}

bool Mouse::IsPressRight()
{
	return ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0);
}
bool Mouse::IsReleseRight()
{
	return (_prevHistory == 2 && _now == 0);
}
bool Mouse::IsPressMiddle()
{
	return ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0);
}
bool Mouse::IsReleseMiddle()
{
	return (_prevHistory == 4 && _now == 0);
}
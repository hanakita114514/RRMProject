#pragma once

#include "Vector2.h"

class UI
{
protected:
	Position _pos;

public:
	UI();
	virtual ~UI();

	//virtual void Update() = 0;
	virtual void Draw() = 0;


};


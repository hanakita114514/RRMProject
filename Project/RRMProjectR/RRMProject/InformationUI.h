#pragma once

#include "Vector2.h"
#include "FPS.h"

class InformationUI
{
private:
	int _filterHandle;

	FPS _fps;
public:
	InformationUI();
	~InformationUI();

	void Draw();
};


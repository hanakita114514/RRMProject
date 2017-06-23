#pragma once

#include "Scene.h"
#include "Timer.h"

class DInput;

class TitleScene : public Scene
{
private:
	Timer _timer;
	DInput* _dinput;

public:
	TitleScene();
	~TitleScene();

	bool Update();
};


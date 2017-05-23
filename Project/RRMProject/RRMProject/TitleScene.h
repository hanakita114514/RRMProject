#pragma once

#include "Scene.h"
#include "Timer.h"

class TitleScene : public Scene
{
private:
	Timer _timer;

public:
	TitleScene();
	~TitleScene();

	bool Update();
};


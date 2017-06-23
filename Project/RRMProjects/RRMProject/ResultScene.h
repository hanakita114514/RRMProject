#pragma once

#include "Scene.h"

class DInput;
class ResultScene : public Scene
{
private:
	DInput* _dinput;
	int _stageId;
public:
	ResultScene();
	ResultScene(LogoIdx state);
	~ResultScene();

	bool Update();
};


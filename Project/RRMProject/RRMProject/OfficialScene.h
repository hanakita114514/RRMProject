#pragma once
#include "Scene.h"

class OfficialScene : public Scene
{
private:
	int _testHandle;
public:
	OfficialScene();
	~OfficialScene();

	bool Update();
};


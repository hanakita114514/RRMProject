#pragma once
#include "Scene.h"

//�e�X�g�p
#include "HPBar.h"
#include "HitPoint.h"

class OfficialScene : public Scene
{
private:
	//�e�X�g
	HitPoint _hp;

public:
	OfficialScene();
	~OfficialScene();

	bool Update();
};


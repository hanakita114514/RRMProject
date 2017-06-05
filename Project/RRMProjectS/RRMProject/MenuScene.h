#pragma once

#include "Scene.h"

class MenuScene : public Scene
{
private:
	int _titleHandle;

	void (MenuScene::*_update)();

	void TitleUpdate();
	void MenuUpdate();
public:
	MenuScene();
	~MenuScene();

	bool Update();
};


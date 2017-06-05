#include "MenuScene.h"
#include <DxLib.h>


MenuScene::MenuScene()
{
	_titleHandle = DxLib::LoadGraph("Resource/img/title.png");
	_update = &MenuScene::TitleUpdate;
}


MenuScene::~MenuScene()
{
}

void 
MenuScene::TitleUpdate()
{
	DxLib::DrawGraph(0, 0, _titleHandle, true);
}

void 
MenuScene::MenuUpdate()
{

}

bool MenuScene::Update()
{
	(this->*_update)();

	return true;
}

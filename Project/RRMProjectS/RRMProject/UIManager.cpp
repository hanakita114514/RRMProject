#include "UIManager.h"



UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void 
UIManager::Create()
{
	_uiFactory.Create();
}

void 
UIManager::Draw()
{
	for (auto& ui : _uiList)
	{
		ui->Draw();
	}
}
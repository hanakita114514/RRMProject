#include "BackgroundRendar.h"
#include "File.h"
#include "DxLib.h"
#include "common.h"
#include <iostream>

BackgroundRendar::BackgroundRendar()
{
}


BackgroundRendar::~BackgroundRendar()
{
}

bool BackgroundRendar::Initialize(const char* imageFilePath)
{

	_filePath = imageFilePath;

	_bgImage = DxLib::LoadGraph(_filePath);
	if (_bgImage == -1)		//ÉGÉâÅ[ÇµÇΩÇ©ÅH
	{
		return false;
	}

	return true;
}

void BackgroundRendar::Draw()
{
	DxLib::DrawExtendGraph(0, 0, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1, _bgImage, true);
}

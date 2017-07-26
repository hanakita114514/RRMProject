#include "BackgroundRendar.h"
#include "File.h"
#include "RRMLib.h"
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

	_bgImage = RRMLib::LoadGraph(_filePath);
	if (_bgImage == -1)		//ÉGÉâÅ[ÇµÇΩÇ©ÅH
	{
		return false;
	}

	return true;
}

void BackgroundRendar::Draw()
{
RRMLib::DrawExtendGraph(0, 0, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1, _bgImage,true,false);}

#include <DxLib.h>
#include "Mouse.h"
#include "common.h"
#include "Edit.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCndLine, int lpCndShow)
{
	if (DxLib::DxLib_Init() == -1)
	{
		return -1;
	}

	ChangeWindowMode(true);
	SetWindowSize(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	Mouse* mouse = new Mouse();
	Edit *edit = new Edit();

	DxLib::SetDrawMode(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		DxLib::ClearDrawScreen();
		mouse->Update();

		mouse->Draw(0, 0);
		edit->Draw();

		DxLib::ScreenFlip();
	}
}
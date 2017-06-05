#include <DxLib.h>
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	GameMain& gameMain = GameMain::Instance();

	gameMain.Init();

	gameMain.GameLoop();

	gameMain.Terminate();

	return 0;
}
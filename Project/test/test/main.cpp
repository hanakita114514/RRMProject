#include "RMMLib.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	if (RRMLib::RRMLib_Init() == -1)
	{
		return -1;
	}

	RRMLib::SetWindowSize(1280, 720);

	int handle = RRMLib::LoadGraph("rei.jpg");

	int x = 0;

	int mp1Handle = RRMLib::LoadSound(L"Sound/y“Œ•û‰i–é´zƒVƒ“ƒfƒŒƒ‰ƒP[ƒW@`_Kagome-KagomeyŒ´‹Èz.mp3");
	int mp2Handle = RRMLib::LoadSound(L"Sound/tukimadetodoke.mp3");
	RRMLib::PlaySoundMem(mp2Handle);

	int frame = 0;

	RRMLib::DJOYPAD_STATE dstate;

	RRMLib::SetSoundVolume(0, mp2Handle);
	long m = RRMLib::GetSoundVolume(mp2Handle);


	while (RRMLib::ProcessMessage() == 0)
	{
		RRMLib::ClearDrawScreen();

		RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 30);
		RRMLib::DrawExtendGraph(0, 0, 1000, 500, handle);
		RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);

		//if (frame++ > 240)
		//{
		//	RRMLib::PauseSound(mpHandle);
		//}

		m = RRMLib::GetSoundVolume(mp2Handle);

		char titlebar[32];
		titlebar[0] = '\0';
		sprintf(titlebar, "%d", m);
		RRMLib::SetMainWindowText(titlebar);

		RRMLib::DrawRectExtendGraph(100, 100, 500, 500, 100, 300, 500, 500, handle, true, false);

		frame += 10;
		RRMLib::SetSoundVolume(frame, mp2Handle);

		RRMLib::DrawBox(0, 0, 100, 100, RRMLib::GetColor(255, 0, 0), false);
		RRMLib::DrawCircle(100, 100, 50, RRMLib::GetColor(255, 255, 255), false);
		RRMLib::DrawPoint(100, 700, 0xffffffff);
		RRMLib::DrawLine(100, 100, 800, 600, 0xffffffff);

		//bool ret = RRMLib::GetJoypadDirectInputState(0, &dstate);

		RRMLib::ScreenFlip();
	}

	RRMLib::RRMLib_End();

	return 0;
}
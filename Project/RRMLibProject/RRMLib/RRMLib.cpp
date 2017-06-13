#include "RRMLib.h" 
#include <Windows.h>
#include <d3d11.h>
#include <D3DX11.h>
#include "Common.h"
#include "DeviceDx11.h"
#include <xnamath.h>
#include "WindowControl.h"
#include "Graphic.h"
#include "DInput.h"
#include "MediaControl.h"
#include "XAudio.h"
#include "SoundManager.h"
#include "GeometryGraph.h"
#include "Renderer.h"

//�C���v�b�g
RRMLib::DInput dinput;

namespace RRMLib
{
	//DirectX�̏�����
	HRESULT InitDirect3D(WindowControl& wc)
	{
		HRESULT result = S_OK;

		DeviceDx11& dev = DeviceDx11::Instance();
		Renderer::Instance().Init();

		return result;

	}

	//�������֐�
	int RRMLib_Init()
	{
		HRESULT result = S_OK;
		WindowControl::Instance().Init();
		DeviceDx11& dev = DeviceDx11::Instance();

		result = dev.Init(WindowControl::Instance());

		if (FAILED(result))
		{
			return -1;
		}

		HWND& hwnd = WindowControl::Instance().WindowHandle();

		//�E�B���h�E�̕\��
		ShowWindow(hwnd, SW_SHOW);

		result = InitDirect3D(WindowControl::Instance());

		if (FAILED(result))
		{
			return -1;
		}

		bool ret = dinput.Init();
		//if (!ret)
		//{
		//	return -1;
		//}

		XAudio::Instance().Init();

		return 0;
	}

	//��n��
	int RRMLib_End()
	{
		MediaControl::Instance().Terminate();
		XAudio::Instance().Terminate();
		return 0;
	}

	//���b�Z�[�W����
	int  ProcessMessage()
	{
		MSG msg = {};

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return -1;
			}
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}

		return 0;
	}



	//��ʂɕ`�悳��Ă�����̂�����
	void ClearDrawScreen()
	{
		Renderer::Instance().Clear();
	}

	//����ʐ؂�ւ�
	int ScreenFlip()
	{
		DeviceDx11& dev = DeviceDx11::Instance();
		HRESULT result = S_OK;
		result = dev.SwapChain()->Present(1, 0);
		if (FAILED(result))
		{
			return -1;
		}

		return 0;
	}

	//�E�B���h�E�T�C�Y�̕ύX
	void SetWindowSize(int width, int height)
	{
		ShowWindow(WindowControl::Instance().WindowHandle(), SW_HIDE);

		HRESULT result = S_OK;
		WindowControl::Instance().Init();
		DeviceDx11& dev = DeviceDx11::Instance();
		WindowControl::Instance().SetGraphMode(width, height);

		dev.Init(WindowControl::Instance());
		HWND& hwnd = WindowControl::Instance().WindowHandle();

		result = InitDirect3D(WindowControl::Instance());

		ShowWindow(hwnd, SW_SHOW);
	}

	//�t���X�N���[�����[�h�ɐݒ�
	void ChangeFullScreenMode(bool fullScreen)
	{
		WindowControl::Instance().ChangeFullScreenMode(fullScreen);
	}

	//�E�B���h�E�e�L�X�g��ݒ�
	void SetMainWindowText(std::string windowName)
	{
		SetWindowText(WindowControl::Instance().WindowHandle(), windowName.c_str());
	}

	//�w�i�F�̕ύX
	void ChangeBackColor(int red, int green, int blue)
	{
		Renderer::Instance().BackGroundColor(red, green, blue);
	}

	//�摜�̓ǂݍ���
	int LoadGraph(std::string filePath)
	{
		int handle = Graphic::Instance().LoadGraph(filePath);

		return handle;
	}

	//�摜��`��
	void DrawGraph(int x, int y, int graphHandle)
	{
		Renderer::Instance().SetZBuffer(false);
		Graphic::Instance().DrawGraph(x, y, graphHandle);
	}
	
	//�摜�̋�`�`��
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		Graphic::Instance().DrawRectGraph(destX, destY, srcX, srcY,
			width, height, graphHandle, transFlag, trunFlag);
	}

	//�摜�̊g�k�`��
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle)
	{
		Renderer::Instance().SetZBuffer(false);
		Graphic::Instance().DrawExtendGraph(lx, ly, rx, ry, handle);
	}

	//�摜�̊g�k��`�`��
	void DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY,
		int srcX, int srcY, int width, int height, int graphHandle, bool transFlag, bool turnFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		Graphic::Instance().DrawRectExtendGraph(destLX, destLY, destRX, destRY,
			srcX, srcY, width, height, graphHandle, transFlag, turnFlag);
	}

	//��`�`��
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		GeometryGraph::Instance().DrawBox(lx, ly, rx, ry, color, fillFlag);
	}
	
	//���`��
	void DrawLine(float lx, float ly, float rx, float ry, unsigned int color)
	{
		Renderer::Instance().SetZBuffer(false);
		GeometryGraph::Instance().DrawLine(lx, ly, rx, ry, color);
	}

	//�_�`��
	void DrawPoint(float x, float y, unsigned int color)
	{
		Renderer::Instance().SetZBuffer(false);
		GeometryGraph::Instance().DrawPoint(x, y, color);
	}

	//�~�`��
	void DrawCircle(float x, float y, float r, unsigned int color, bool fillflag)
	{
		Renderer::Instance().SetZBuffer(false);
		GeometryGraph::Instance().DrawCircle(x, y, r, color, fillflag);
	}

	//�F�����擾
	unsigned int  GetColor(unsigned char red, unsigned char green, unsigned char blue)
	{
		unsigned int color = 0;
		color = red << 24 | green << 16 | blue << 8;
		color |= 0x000000ff;
		return color;
	}

	//�u�����h���[�h��ݒ�
	void SetBlendMode(int mode, int pal)
	{
		switch (mode)
		{
		case RRM_BLENDMODE_NONE:
			Renderer::Instance().DefaultBlend();
			break;
		case RRM_BLENDMODE_ALPHA:
			Renderer::Instance().AlphaBlend(pal);
			break;
		default:
			break;
		}
	}


	//DInput
	bool GetJoypadDirectInputState(int inputType, DJOYPAD_STATE* joystate)
	{
		DIJOYSTATE js;
		bool ret = false;
		const int povNum = 4;
		const int buttonNum = 32;

		ret = dinput.GetJoyState(js);

		joystate->x = js.lX;
		joystate->y = js.lY;
		joystate->z = js.lZ;

		joystate->rX = js.lRx;
		joystate->rY = js.lRy;
		joystate->rZ = js.lRz;

		joystate->slider[0] = js.rglSlider[0];
		joystate->slider[1] = js.rglSlider[1];

		for (int i = 0; i < povNum; ++i)
		{
			joystate->pov[i] = js.rgdwPOV[i];
		}

		for (int i = 0; i < buttonNum; ++i)
		{
			joystate->buttons[i] = js.rgbButtons[i];
		}

		return ret;
	}

	//���y��ǂݍ���
	int LoadSound(BSTR filePath)
	{
		int handle = MediaControl::Instance().Load(filePath);
		return handle;
	}

	// ���y���Đ�����
	// handle LodaSound�œǂݍ��񂾃n���h�����w��
	void PlaySoundMem(int handle)
	{
		MediaControl::Instance().Play(handle);
	}

	// ���y���ꎞ��~������
	void PauseSound(int handle)
	{
		MediaControl::Instance().Pause(handle);
	}

	//���y���~�߂�
	void StopSound(int handle)
	{
		MediaControl::Instance().Stop(handle);
	}

	//���y�̃{�����[����ύX����
	//0�`10000
	void SetSoundVolume(long vol, int handle)
	{
		MediaControl::Instance().SetVolume(vol, handle);
	}

	//���y�̃{�����[�����擾����
	long GetSoundVolume(int handle)
	{
		long vol = MediaControl::Instance().GetVolume(handle);
		return vol;
	}
}
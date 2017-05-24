#include "RMMLib.h" 
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

//�����_���[
ID3D11RenderTargetView* _rtv;

ID3D11Texture2D* _depthTexture2D;	//�[�x�p�e�N�X�`��
ID3D11DepthStencilView* _dsv;	//�[�x�r���[


//�C���v�b�g
DInput dinput;

namespace RRMLib
{
	//DirectX�̏�����
	HRESULT InitDirect3D(WindowControl& wc)
	{
		HRESULT result = S_OK;

		DeviceDx11& dev = DeviceDx11::Instance();


		//�o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g�r���[(RTV)���쐬
		ID3D11Texture2D* pBack;
		//�o�b�N�o�b�t�@�̃T�[�t�F�C�X���V�F�[�_���\�[�X(�e�N�X�`��)�Ƃ��Ĕ����o��
		result = dev.SwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);

		//���̃e�N�X�`���������_�[�^�[�Q�b�g�Ƃ���悤�ȃ����_�[�^�[�Q�b�g�r���[���쐬
		result = dev.Device()->CreateRenderTargetView(pBack, nullptr, &_rtv);

		pBack->Release();

		//�f�v�X�X�e���V���r���[(DSV)���쐬
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = wc.WindowWidth();
		descDepth.Height = wc.WindowHeight();
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		result = dev.Device()->CreateTexture2D(&descDepth, nullptr, &_depthTexture2D);
		result = dev.Device()->CreateDepthStencilView(_depthTexture2D, nullptr, &_dsv);

		//�r���[�|�[�g�̐ݒ�
		D3D11_VIEWPORT vp;
		vp.Width = wc.WindowWidth();
		vp.Height = wc.WindowHeight();
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		dev.Context()->RSSetViewports(1, &vp);

		//�����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[���Z�b�g
		dev.Context()->OMSetRenderTargets(1, &_rtv, _dsv);

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
		DeviceDx11& dev = DeviceDx11::Instance();
		float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA

		dev.Context()->ClearRenderTargetView(_rtv, color);

		dev.Context()->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
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

	//�摜�̓ǂݍ���
	int LoadGraph(std::string filePath)
	{
		int handle = Graphic::Instance().LoadGraph(filePath);

		return handle;
	}

	//�摜��`��
	void DrawGraph(int x, int y, int graphHandle)
	{
		Graphic::Instance().DrawGraph(x, y, graphHandle);
	}
	
	//�摜�̋�`�`��
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag)
	{
		Graphic::Instance().DrawRectGraph(destX, destY, srcX, srcY,
			width, height, graphHandle, transFlag, trunFlag);
	}

	//�摜�̊g�k�`��
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle)
	{
		Graphic::Instance().DrawExtendGraph(lx, ly, rx, ry, handle);
	}

	//��`�`��
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag)
	{
		GeometryGraph::Instance().DrawBox(lx, ly, rx, ry, color, fillFlag);
	}

	//�F�����擾
	unsigned int  GetColor(unsigned char red, unsigned char green, unsigned char blue)
	{
		unsigned int color = 0;
		color = red << 24 | green << 16 | blue << 8;
		color |= 0x000000ff;
		return color;
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
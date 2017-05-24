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

//レンダラー
ID3D11RenderTargetView* _rtv;

ID3D11Texture2D* _depthTexture2D;	//深度用テクスチャ
ID3D11DepthStencilView* _dsv;	//深度ビュー


//インプット
DInput dinput;

namespace RRMLib
{
	//DirectXの初期化
	HRESULT InitDirect3D(WindowControl& wc)
	{
		HRESULT result = S_OK;

		DeviceDx11& dev = DeviceDx11::Instance();


		//バックバッファのレンダーターゲットビュー(RTV)を作成
		ID3D11Texture2D* pBack;
		//バックバッファのサーフェイスをシェーダリソース(テクスチャ)として抜き出す
		result = dev.SwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);

		//そのテクスチャをレンダーターゲットとするようなレンダーターゲットビューを作成
		result = dev.Device()->CreateRenderTargetView(pBack, nullptr, &_rtv);

		pBack->Release();

		//デプスステンシルビュー(DSV)を作成
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

		//ビューポートの設定
		D3D11_VIEWPORT vp;
		vp.Width = wc.WindowWidth();
		vp.Height = wc.WindowHeight();
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		dev.Context()->RSSetViewports(1, &vp);

		//レンダーターゲットビューとデプスステンシルビューをセット
		dev.Context()->OMSetRenderTargets(1, &_rtv, _dsv);

		return result;

	}

	//初期化関数
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

		//ウィンドウの表示
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

	//後始末
	int RRMLib_End()
	{
		MediaControl::Instance().Terminate();
		XAudio::Instance().Terminate();
		return 0;
	}

	//メッセージ処理
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



	//画面に描画されているものを消す
	void ClearDrawScreen()
	{
		DeviceDx11& dev = DeviceDx11::Instance();
		float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA

		dev.Context()->ClearRenderTargetView(_rtv, color);

		dev.Context()->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	//裏画面切り替え
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

	//ウィンドウサイズの変更
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

	//フルスクリーンモードに設定
	void ChangeFullScreenMode(bool fullScreen)
	{
		WindowControl::Instance().ChangeFullScreenMode(fullScreen);
	}

	//ウィンドウテキストを設定
	void SetMainWindowText(std::string windowName)
	{
		SetWindowText(WindowControl::Instance().WindowHandle(), windowName.c_str());
	}

	//画像の読み込み
	int LoadGraph(std::string filePath)
	{
		int handle = Graphic::Instance().LoadGraph(filePath);

		return handle;
	}

	//画像を描画
	void DrawGraph(int x, int y, int graphHandle)
	{
		Graphic::Instance().DrawGraph(x, y, graphHandle);
	}
	
	//画像の矩形描画
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag)
	{
		Graphic::Instance().DrawRectGraph(destX, destY, srcX, srcY,
			width, height, graphHandle, transFlag, trunFlag);
	}

	//画像の拡縮描画
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle)
	{
		Graphic::Instance().DrawExtendGraph(lx, ly, rx, ry, handle);
	}

	//矩形描画
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag)
	{
		GeometryGraph::Instance().DrawBox(lx, ly, rx, ry, color, fillFlag);
	}

	//色情報を取得
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

	//音楽を読み込む
	int LoadSound(BSTR filePath)
	{
		int handle = MediaControl::Instance().Load(filePath);
		return handle;
	}

	// 音楽を再生する
	// handle LodaSoundで読み込んだハンドルを指定
	void PlaySoundMem(int handle)
	{
		MediaControl::Instance().Play(handle);
	}

	// 音楽を一時停止させる
	void PauseSound(int handle)
	{
		MediaControl::Instance().Pause(handle);
	}

	//音楽を止める
	void StopSound(int handle)
	{
		MediaControl::Instance().Stop(handle);
	}

	//音楽のボリュームを変更する
	//0～10000
	void SetSoundVolume(long vol, int handle)
	{
		MediaControl::Instance().SetVolume(vol, handle);
	}

	//音楽のボリュームを取得する
	long GetSoundVolume(int handle)
	{
		long vol = MediaControl::Instance().GetVolume(handle);
		return vol;
	}
}
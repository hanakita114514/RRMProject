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
#include "GraphList.h"
#include "Keyboard.h"

//インプット
static RRMLib::DInput dinput;
static RRMLib::Keyboard keyboard;

//グラフィック関係
static Graphic graphic;
static GeometryGraph geometryGraph;

namespace RRMLib
{
	//DirectXの初期化
	HRESULT InitDirect3D(WindowControl& wc)
	{
		HRESULT result = S_OK;

		DeviceDx11& dev = DeviceDx11::Instance();
		Renderer::Instance().Init();

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

		//インプットの初期化
		bool ret = dinput.Init();
		//if (!ret)
		//{
		//	return -1;
		//}

		keyboard.Init();

		//音楽関係の初期化
		XAudio::Instance().Init();

		//画像関係の初期化
		ret = graphic.Init();
		if (!ret)
		{
			return -1;
		}
		ret = geometryGraph.Init();
		if (!ret)
		{
			return -1;
		}

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
		Renderer::Instance().Clear();
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
		HWND& hwnd = WindowControl::Instance().WindowHandle();
		ShowWindow(WindowControl::Instance().WindowHandle(), SW_HIDE);
		//DestroyWindow(hwnd);


		HRESULT result = S_OK;
		WindowControl::Instance().Init();
		DeviceDx11& dev = DeviceDx11::Instance();
		WindowControl::Instance().SetGraphMode(width, height);

		dev.Init(WindowControl::Instance());

		result = InitDirect3D(WindowControl::Instance());

		//MoveWindow(hwnd, 0, 0, width, height, false);

		graphic.Terminate();
		geometryGraph.Terminate();

		graphic.Init();
		geometryGraph.Init();

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

	//背景色の変更
	void ChangeBackColor(int red, int green, int blue)
	{
		Renderer::Instance().BackGroundColor(red, green, blue);
	}

	//メッセージボックス
	void ShowMessageBox(std::string text, std::string title)
	{
		HWND hwnd = WindowControl::Instance().WindowHandle();
		MessageBox(hwnd, text.c_str(), title.c_str(), MB_OK);
	}

	//画像の読み込み
	int LoadGraph(std::string filePath)
	{
		int handle = graphic.LoadGraph(filePath);

		return handle;
	}

	//画像の分割読み込み
	int LoadDivGraph(std::string filePath, int allNum, int xNum, int yNum, int width, int height, int* handleBuf)
	{
		int ret = graphic.LoadDivGraph(filePath, allNum, xNum, yNum, width, height, handleBuf);
		return ret;
	}

	//読み込んだ画像を削除
	void DeleteGraph(int handle)
	{
		graphic.DeleteGraph(handle);
	}

	//画像を描画
	void DrawGraph(float x, float y, int graphHandle, bool transFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		graphic.DrawGraph(x, y, graphHandle, transFlag);
	}
	
	//画像の矩形描画
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		graphic.DrawRectGraph(destX, destY, srcX, srcY,
			width, height, graphHandle, transFlag, trunFlag);
	}


	//画像の拡縮描画
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle, bool transFlag, bool turnFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		graphic.DrawExtendGraph(lx, ly, rx, ry, handle, transFlag, turnFlag);
	}

	//画像の拡縮矩形描画
	void DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY,
		int srcX, int srcY, int width, int height, int graphHandle, bool transFlag, bool turnFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		graphic.DrawRectExtendGraph(destLX, destLY, destRX, destRY,
			srcX, srcY, width, height, graphHandle, transFlag, turnFlag);
	}

	//画像の回転描画
	void DrawRotaGraph(float x, float y, double angle, int graphHadle, bool transFlag, bool turnFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		graphic.DrawRotaGraph(x, y, angle, graphHadle, transFlag, turnFlag);
	}

	//矩形描画
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag)
	{
		Renderer::Instance().SetZBuffer(false);
		geometryGraph.DrawBox(lx, ly, rx, ry, color, fillFlag);
	}
	
	//線描画
	void DrawLine(float lx, float ly, float rx, float ry, unsigned int color)
	{
		Renderer::Instance().SetZBuffer(false);
		geometryGraph.DrawLine(lx, ly, rx, ry, color);
	}

	//点描画
	void DrawPoint(float x, float y, unsigned int color)
	{
		Renderer::Instance().SetZBuffer(false);
		geometryGraph.DrawPoint(x, y, color);
	}

	//円描画
	void DrawCircle(float x, float y, float r, unsigned int color, bool fillflag)
	{
		Renderer::Instance().SetZBuffer(false);
		geometryGraph.DrawCircle(x, y, r, color, fillflag);
	}

	//色情報を取得
	unsigned int  GetColor(unsigned char red, unsigned char green, unsigned char blue)
	{
		unsigned int color = 0;
		color = red << 24 | green << 16 | blue << 8;
		color |= 0x000000ff;
		return color;
	}

	//ブレンドモードを設定
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
		DIJOYSTATE js = {};
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

	//キーボード入力
	bool GetKeyboardState(char* keyBuf)
	{
		bool ret = keyboard.GetKeyState(keyBuf);
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

	//音楽を最初から再生する
	void PlayFromStart(int handle)
	{
		MediaControl::Instance().PlayFromStart(handle);
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

	//取得した音楽ハンドルを削除する
	void DeleteSound(int handle)
	{
		MediaPlayer* mp = (MediaPlayer*)handle;
		mp->Terminate();
		delete(mp);
	}
}
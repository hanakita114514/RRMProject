#pragma once

#include <Windows.h>
#include "WindowControl.h"

//DirectX プロとタイプ宣言
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RasterizerState;

class DeviceDx11
{
private:
	HWND _hwnd;
	IDXGISwapChain* _swapchain;
	ID3D11Device* _device;
	ID3D11DeviceContext* _context;

	//カリングON/OFFのためのラスタライザーステート
	ID3D11RasterizerState* _cullingOnState;		//裏面非描画
	ID3D11RasterizerState* _cullingOffState;	//裏面描画

												//シングルトンなのでコンストラクタをprivateへ
	DeviceDx11();
	//コピー、代入を禁止
	DeviceDx11(const DeviceDx11&);
	DeviceDx11& operator=(const DeviceDx11&);

public:
	~DeviceDx11();

	//インスタンスを返す
	static DeviceDx11& Instance()
	{
		static DeviceDx11 instance;

		return instance;
	}

	//DirectXの初期化
	HRESULT Init(WindowControl& wc);

	//デバイスの再設定
	HRESULT Reset(WindowControl& wc);

	//デバイス関連のアクセサを提供
	IDXGISwapChain* SwapChain();	//_swapchainを返す
	ID3D11Device* Device();	//_deviceを返す
	ID3D11DeviceContext* Context(); //

	//終了処理
	void Terminate();

									//カリングのON/OFFを切り替える
									//flg trueのときカリングON, falseのときカリングOFF
	void SetCullingFlg(bool flg);

	HWND WindowHandle();
};


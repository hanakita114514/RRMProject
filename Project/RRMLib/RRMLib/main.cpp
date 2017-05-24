#include <Windows.h>
#include <d3d11.h>
#include <D3DX11.h>
#include "Common.h"
#include "DeviceDx11.h"
#include <xnamath.h>
#include "WindowControl.h"
#include "Graphic.h"
#include "DInput.h"
#include <dinput.h>

#include "SoundManager.h"
#include "XAudio.h"
#include <stdio.h>

#include "MediaPlayer.h"
#include "MediaControl.h"

#include "GeometryGraph.h"

//レンダラー
ID3D11RenderTargetView* _rtv;

ID3D11Texture2D* _depthTexture2D;	//深度用テクスチャ
ID3D11DepthStencilView* _dsv;	//深度ビュー

struct MatrixForShader
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX proj;
};


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

HRESULT ResetDirect3D(WindowControl& wc)
{
	HRESULT hr;

	DeviceDx11& dev = DeviceDx11::Instance();

	hr = dev.Reset(wc);

	if (FAILED(hr))
	{
		return hr;
	}

	ID3D11RenderTargetView* rtv = nullptr;
	dev.Context()->OMSetRenderTargets(1, &rtv, nullptr);
	_rtv->Release();
	_dsv->Release();

	hr = dev.SwapChain()->ResizeBuffers(2,
		0,
		0,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		0);

	if (FAILED(hr))
	{
		return hr;
	}

	ID3D11Texture2D* tex = nullptr;
	D3D11_TEXTURE2D_DESC tex2ddesc =
	{
		wc.WindowHeight(), wc.WindowWidth(), 1, 1,	//width , height, mip, array
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		{1, 0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL,
		0,	//CPU flags
		0	//misc flags
	};

	hr = dev.Device()->CreateTexture2D(&tex2ddesc, nullptr, &tex);

	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC vdesc =
	{
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		D3D11_DSV_DIMENSION_TEXTURE2D
	};

	dev.Device()->CreateDepthStencilView(
		tex,
		&vdesc,
		&_dsv
	);

	tex->Release();

	dev.Context()->OMSetRenderTargets(1,
		&_rtv,
		_dsv);

	D3D11_VIEWPORT viewport =
	{
		0, 0, wc.WindowWidth(), wc.WindowHeight(), 0.0f, 1.0f
	};

	dev.Context()->RSSetViewports(1, &viewport);


	return hr;
}

//ウィンドウのメッセージを取得
//成功 : 0  エラー又はウィンドウが閉じられた : -1
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

//色情報を取得
// 0 ～ 255で指定
unsigned int GetColor(unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned int color = 0;
	color = red << 24 | green << 16 | blue << 8;
	color |= 0x000000ff;
	return color;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの作成
	//WindowControl winControl;
	WindowControl::Instance().Init();
	WindowControl::Instance().SetGraphMode(1280, 720);

	HWND hwnd = WindowControl::Instance().WindowHandle();

	DeviceDx11& dev = DeviceDx11::Instance();

	dev.Init(WindowControl::Instance());

	//ウィンドウの表示
	ShowWindow(hwnd, SW_SHOW);

	InitDirect3D(WindowControl::Instance());


	//ResetDirect3D(WindowControl::Instance());

	Graphic& graphic = Graphic::Instance();
	int handle = graphic.LoadGraph("rei.jpg");
	int rectHandle = graphic.LoadGraph("bomb.png");

	//WindowControl::Instance().ChangeFullScreenMode(true);


	struct Position
	{
		float x, y, z;
	};

	Position vertices[] =
	{
		//４面
		//{ -1, -1, -1 },
		//{ -1, 1, -1 },
		//{ 1, -1, -1 },
		//{ 1,  1, -1},
		//{ 1, -1, 1 },
		//{ 1, 1, 1 },
		//{ -1, -1, 1  },
		//{ -1, 1, 1},
		//{ -1, -1, -1 },
		//{ -1, 1, -1 },

		{1,1,0 },
		{1,-1,0},
		{-1,-1,0},
		{ -1,-1,0 },
		{ 1,-1,0 },
		{ 1,1,0 },

	};

	ID3D11Buffer* vb;

	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices);
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DEFAULT;
	bufdesc.CPUAccessFlags = 0;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Position) * sizeof(vertices);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	HRESULT result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	unsigned int stride = sizeof(Position);
	unsigned int offset = 0;

	//頂点バッファのセット
	dev.Context()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

	//プリミティブトポロジーの設定
	//dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//シェーダのロード、コンパイル
	ID3DBlob* compileShader = nullptr;
	ID3DBlob* shaderError = nullptr;

	result = D3DX11CompileFromFile("BaseShader.hlsl",
		nullptr,
		nullptr,
		"BaseVS",
		"vs_5_0",
		0,
		0,
		nullptr,
		&compileShader,
		&shaderError,
		nullptr
	);

	//シェーダの作成
	ID3D11VertexShader* vs = nullptr;

	result = dev.Device()->CreateVertexShader(compileShader->GetBufferPointer(),
		compileShader->GetBufferSize(),
		nullptr,
		&vs);

	//インプットレイアウトの設定
	D3D11_INPUT_ELEMENT_DESC inputElemDescs[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	ID3D11InputLayout* inputLayout = nullptr;
	result = dev.Device()->CreateInputLayout(inputElemDescs,
		sizeof(inputElemDescs) / sizeof(inputElemDescs[0]),
		compileShader->GetBufferPointer(),
		compileShader->GetBufferSize(),
		&inputLayout);

	compileShader->Release();

	//ピクセルシェーダの作成
	result = D3DX11CompileFromFile("BaseShader.hlsl",
		nullptr,
		nullptr,
		"BasePS",
		"ps_5_0",
		0,
		0,
		nullptr,
		&compileShader,
		&shaderError,
		nullptr
	);

	ID3D11PixelShader* ps = nullptr;

	result = dev.Device()->CreatePixelShader(compileShader->GetBufferPointer(),
		compileShader->GetBufferSize(),
		nullptr,
		&ps);

	compileShader->Release();

	dev.Context()->IASetInputLayout(inputLayout);
	dev.Context()->VSSetShader(vs, nullptr, 0);
	dev.Context()->PSSetShader(ps, nullptr, 0);


	//ワールド行列を作成
	XMMATRIX world = XMMatrixRotationY(0);

	//ビュー行列を作成
	XMVECTOR eye = { 0, 0, -5 };
	XMVECTOR target = { 0,0,1 };
	XMVECTOR up = { 0, 1, 0 };

	XMMATRIX view = XMMatrixLookAtLH(eye, target, up);

	//プロジェクション行列を作成
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PI / 4, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	MatrixForShader mfs;

	mfs.world = world;
	mfs.view = view;
	mfs.proj = proj;

	XMMATRIX matrix = world * view * proj;

	//行列コンスタントバッファの作成
	D3D11_BUFFER_DESC cbuffdesc = {};
	cbuffdesc.Usage = D3D11_USAGE_DYNAMIC;
	cbuffdesc.ByteWidth = sizeof(MatrixForShader);
	cbuffdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//コンスタントバッファ
	cbuffdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//CPUから書き換え可能

	D3D11_SUBRESOURCE_DATA csubdata = {};
	csubdata.pSysMem = &mfs;

	ID3D11Buffer* cbuffer = nullptr;
	result = dev.Device()->CreateBuffer(&cbuffdesc, &csubdata, &cbuffer);
	dev.Context()->VSSetConstantBuffers(0, 1, &cbuffer);

	//int handle = Graphic::LoadGraph("rei.jpg");


	float angle = 0;

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA

	DInput input;
	DIJOYSTATE js;

	int frame = 0;

	SoundManager::Instance().Init();

	//SoundManager::Instance().Play(0);

	XAudio::Instance().Init();
	//XAudio::Instance().Play();
	//XAudio::Instance().Load("Sound/arabianjewel.WAV");
	//XAudio::Instance().Load("Sound/【東方地霊殿】少女さとり　3rd_eye【原曲】.mp3");
	//XAudio::Instance().Play();

	//MediaPlayer mp(L"Sound/【東方地霊殿】少女さとり　3rd_eye【原曲】.mp3");
	//mp.Play();

	int mhandle = MediaControl::Instance().Load(L"Sound/tukimadetodoke.mp3");
	int m1handle = MediaControl::Instance().Load(L"Sound/【東方地霊殿】少女さとり　3rd_eye【原曲】.mp3");
	MediaControl::Instance().Play(m1handle);

	GeometryGraph& gg = GeometryGraph::Instance();


	unsigned int red = GetColor(255, 0, 0);
	unsigned int green = GetColor(0, 255, 0);
	unsigned int blue = GetColor(0, 0, 255);

	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		dev.Context()->ClearRenderTargetView(_rtv, color);

		dev.Context()->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

		//world = XMMatrixRotationY(angle);
		//angle += 0.01f;

		//D3D11_MAPPED_SUBRESOURCE mapSub = {};
		//dev.Context()->Map(cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapSub);
		//mfs.world = world;
		//memcpy(mapSub.pData, &mfs, sizeof(MatrixForShader));
		//dev.Context()->Unmap(cbuffer, 0);

		//dev.Context()->Draw(6, 0);

		input.ReadInput();
		bool result = input.GetJoyState(js);
		char       titlebar[32];
		titlebar[0] = '\0';

		if (result)
		{
			strcat(titlebar, "true");
		}
		else
		{
			strcat(titlebar, "false");
		}

		HWND hwnd = WindowControl::Instance().WindowHandle();

		SetWindowText(hwnd, titlebar);

		SoundManager::Instance().Update();

		//graphic.DrawGraph(0, 0, handle);
		//graphic.DrawGraph(0, 0, rectHandle);
		//graphic.DrawRectGraph(0, 0, 0 + ((frame % 60) / 10) * 32, 0, 32, 32, rectHandle, false, false);
		++frame;
		graphic.DrawExtendGraph(0, 0, 1000 , 700, handle);

		//赤
		gg.Instance().DrawBox(50, 50, 100, 100, GetColor(255,0,0), true);
		//緑
		gg.Instance().DrawBox(100, 50, 150, 100, GetColor(0, 255, 0), true);
		//青
		gg.Instance().DrawBox(150, 50, 200, 100, GetColor(0, 0, 255), true);
		//白
		gg.Instance().DrawBox(200, 50, 250, 100, GetColor(255, 255, 255), true);

		graphic.DrawExtendGraph(600, 0, 1500, 700, handle);


		dev.SwapChain()->Present(1, 0);
	}

	SoundManager::Instance().Terminate();
	XAudio::Instance().Terminate();
	MediaControl::Instance().Terminate();

	return 0;
}
#include <Windows.h>
#include <d3d11.h>
#include <D3DX11.h>
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

#include <Shlwapi.h>
#include "Renderer.h"

#include "GraphList.h"
#include "Keyboard.h"
#include "PMDLoader.h"
#include "PMDMesh.h"

#include <thread>

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

	Renderer::Instance().Init();

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

	//ID3D11RenderTargetView* rtv = nullptr;
	//dev.Context()->OMSetRenderTargets(1, &rtv, nullptr);
	//_rtv->Release();
	//_dsv->Release();

	//hr = dev.SwapChain()->ResizeBuffers(2,
	//	0,
	//	0,
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	0);

	//if (FAILED(hr))
	//{
	//	return hr;
	//}

	//ID3D11Texture2D* tex = nullptr;
	//D3D11_TEXTURE2D_DESC tex2ddesc =
	//{
	//	wc.WindowHeight(), wc.WindowWidth(), 1, 1,	//width , height, mip, array
	//	DXGI_FORMAT_D24_UNORM_S8_UINT,
	//	{1, 0},
	//	D3D11_USAGE_DEFAULT,
	//	D3D11_BIND_DEPTH_STENCIL,
	//	0,	//CPU flags
	//	0	//misc flags
	//};

	//hr = dev.Device()->CreateTexture2D(&tex2ddesc, nullptr, &tex);

	//if (FAILED(hr))
	//{
	//	return hr;
	//}

	//D3D11_DEPTH_STENCIL_VIEW_DESC vdesc =
	//{
	//	DXGI_FORMAT_D24_UNORM_S8_UINT,
	//	D3D11_DSV_DIMENSION_TEXTURE2D
	//};

	//dev.Device()->CreateDepthStencilView(
	//	tex,
	//	&vdesc,
	//	&_dsv
	//);

	//tex->Release();

	//dev.Context()->OMSetRenderTargets(1,
	//	&_rtv,
	//	_dsv);

	//D3D11_VIEWPORT viewport =
	//{
	//	0, 0, wc.WindowWidth(), wc.WindowHeight(), 0.0f, 1.0f
	//};

	//dev.Context()->RSSetViewports(1, &viewport);


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

void CreateFont()
{
	DeviceDx11& dev = DeviceDx11::Instance();

	//フォントを使えるようにする
	DESIGNVECTOR design;
	HRESULT result = AddFontResourceEx(
		"apjfont/APJapanesefont.ttf",
		FR_PRIVATE,
		&design
	);

	//フォントの生成
	LOGFONT lf = {
		300,0,0,0,0,0,0,0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("あんずもじ湛")
	};

	char* fontChar = "あいうえお";

	HFONT hFont = CreateFontIndirect(&lf);
	HDC hdc = GetDC(nullptr);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	UINT code = (UINT)fontChar;

	//フォントビットマップ取得
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutline(
		hdc,
		code,
		GGO_GRAY4_BITMAP,
		&GM,
		0,
		nullptr,
		&Mat);
	BYTE* ptr = new BYTE[size];
	GetGlyphOutline(
		hdc,
		code,
		GGO_GRAY4_BITMAP,
		&GM,
		size,
		ptr,
		&Mat);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(nullptr, hdc);

	//CPU書き込みができるテクスチャを作成
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = GM.gmCellIncX;
	desc.Height = TM.tmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	//RGBA(255,255,255,255)タイプ
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D* tex2D;
	result = dev.Device()->CreateTexture2D(&desc, 0, &tex2D);

	//フォント情報をテクスチャに書き込む部分
	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	result = dev.Context()->Map(
		tex2D,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource);

	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	ID3D11ShaderResourceView* fontSRV;

	result = dev.Device()->CreateShaderResourceView(tex2D, &srvDesc, &fontSRV);



	BYTE* pBits = (BYTE*)hMappedResource.pData;
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iofs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX
		+ (4 - (GM.gmBlackBoxX % 4));
	int iBmp_h = GM.gmBlackBoxY;
	int level = 17;
	int x, y;
	DWORD Alpha, Color;
	memset(pBits, 0, hMappedResource.RowPitch * TM.tmHeight);

	for (y = iofs_y; y < iofs_y + iBmp_h; y++)
	{
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++)
		{
			Alpha =
				(255 * ptr[x - iOfs_x + iBmp_w * (y - iofs_y)])
				/ (level - 1);
			Color = 0x00ffffff | (Alpha << 24);

			memcpy(
				(BYTE*)pBits
				+ hMappedResource.RowPitch * y + 4 * x,
				&Color,
				sizeof(DWORD));
		}
	}

	dev.Context()->Unmap(tex2D, 0);
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

	Graphic graphic;
	graphic.Init();
	GeometryGraph gg;
	gg.Init();
	int handle = graphic.LoadGraph("rei.jpg");

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

	DInput input;
	input.Init();
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



	unsigned int red = GetColor(255, 0, 0);
	unsigned int green = GetColor(0, 255, 0);
	unsigned int blue = GetColor(0, 0, 255);

	//int effectHandle = graphic.LoadGraph("Down.png");

	int dsBuf[25];
	graphic.LoadDivGraph("rei.jpg", 25, 5, 5, 384, 216, dsBuf);

	int h = 0;

	ID3DX11ThreadPump* threadPump;
	result = D3DX11CreateThreadPump(0, 0, &threadPump);

	HRESULT phr;
	h = graphic.LoadTexThread("rei.jpg", &phr, threadPump);

	int x = 0;

	const double PI = 3.141592f;

	Keyboard key;
	key.Init();
	char keyBuf[256];

	PMDLoader loader;
	PMDMesh* reimu = loader.Load("Model/博麗霊夢ver100/博麗霊夢ver100.pmd");

	int filterHandle = graphic.LoadGraph("filter1.png");
	Renderer::Instance().BackGroundColor(255, 255, 255);

	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		Renderer::Instance().Clear();

		//world = XMMatrixRotationY(angle);
		//angle += 0.01f;

		//D3D11_MAPPED_SUBRESOURCE mapSub = {};
		//dev.Context()->Map(cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapSub);
		//mfs.world = world;
		//memcpy(mapSub.pData, &mfs, sizeof(MatrixForShader));
		//dev.Context()->Unmap(cbuffer, 0);

		//dev.Context()->Draw(6, 0);

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

		if (js.lY > 200)
		{
			MediaControl::Instance().Play(m1handle);
		}


		HWND hwnd = WindowControl::Instance().WindowHandle();

		SetWindowText(hwnd, titlebar);

		input.ReadInput();


		SoundManager::Instance().Update();

		//graphic.DrawGraph(0, 0, handle);
		//graphic.DrawGraph(0, 0, rectHandle);
		//graphic.DrawRectGraph(0, 0, 0 + ((frame % 60) / 10) * 32, 0, 32, 32, rectHandle, false, false);
		//++frame;
		//graphic.DrawExtendGraph(0, 0, 1000 , 700, handle);


		Renderer::Instance().SetZBuffer(false);
		DeviceDx11::Instance().SetCullingFlg(false);

		//graphic.DrawGraph(x, 0, handle, true);

		for (int i = 0; i < 200; i++)
		{
			//graphic.DrawGraph(x, 0, handle, true);
			//graphic.DrawExtendGraph(x, 0, 1000, 700, handle, true, false);
			//graphic.DrawRectGraph(x, 0, 100, 100, 300, 300, handle, true, true);
			//graphic.DrawRectGraph(0, 0, 100, 100, 500, 500, handle, true, true);
		}

		//graphic.DrawRectExtendGraph(0, 0, 1000, 500, 100, 300, 500, 500, dsBuf[0], true, false);

		//graphic.DrawExtendGraph(0, 0, 1000, 700, ds);

		//graphic.DrawGraph(0 * 384, 0 * 216, dsBuf[0], true);
		//graphic.DrawGraph(1 * 384, 0 * 216, dsBuf[1]);

		angle += 0.01f;

		//graphic.DrawRotaGraph(500, 300, angle, handle, true, false);

		//graphic.DrawGraph(x, 0, handle);

		//gg.DrawBox(500, 300, 510, 310, 0xffffffff, true);

		//GraphList::Instance().Add(graphic.DrawGraph(0, 0, handle));

		//赤
		//gg.DrawBox(50, 50, 100, 100, GetColor(255,0,0), true);
		//緑
		//gg.DrawBox(100, 50, 150, 100, GetColor(0, 255, 0), true);
		//青
		//gg.DrawBox(150, 50, 200, 100, GetColor(0, 0, 255), true);
		//白
		//gg.DrawBox(200, 50, 250, 100, GetColor(255, 255, 255), true);

		//gg.DrawLine(0, 100, 200, 100, GetColor(255, 0, 0));

		//gg.DrawPoint(50, 200, GetColor(255, 255, 0));

		//gg.DrawLine(50, 50, 100, 50, 0xffffffff);

		//graphic.DrawGraph(0, 0, effectHandle);

		//Renderer::Instance().AlphaBlend(180);
		//graphic.DrawGraph(0, 0, handle);
		//Renderer::Instance().DefaultBlend();

		//graphic.DrawRectExtendGraph(0, 0, 500, 500, 0, 0, 600, 600, handle, true, false);

		//graphic.DrawExtendGraph(0, 0, 1500, 700, handle, true, true);

		//GraphList::Instance().Draw();

		Renderer::Instance().Test();
		graphic.DrawGraph(0, 0, filterHandle, true);

		result = key.GetKeyState(keyBuf);

		if (keyBuf[DIK_LEFT])
		{
			x--;
		}
		if (keyBuf[DIK_RIGHT])
		{
			x++;
		}

		dev.SwapChain()->Present(1, 0);
	}

	graphic.DeleteGraph(handle);

	SoundManager::Instance().Terminate();
	XAudio::Instance().Terminate();
	MediaControl::Instance().Terminate();

	return 0;
}
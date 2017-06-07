#include "DeviceDx11.h"
#include <d3d11.h>
#include "Common.h"

DeviceDx11::DeviceDx11()
{
}

DeviceDx11::DeviceDx11(const DeviceDx11&)
{

}

DeviceDx11::~DeviceDx11()
{
}

HRESULT 
DeviceDx11::Init(WindowControl& wc)
{

	HWND hwnd = wc.WindowHandle();
	HRESULT result = S_OK;

	//デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferCount = 1; //バックバッファの数1
	sd.BufferDesc.Width = wc.WindowWidth();
	sd.BufferDesc.Height = wc.WindowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//バックバッファのフォーマット
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = wc.WindowHandle();
	sd.SampleDesc.Count = 1;//サンプリング数 
	sd.Windowed = TRUE;//ウィンドウモード

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0; //使用するフィーチャDirectX11
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;

	//デバイスの作成とスワップチェインの生成
	 result = D3D11CreateDeviceAndSwapChain(nullptr,	//既定のアダプタを使用
		D3D_DRIVER_TYPE_HARDWARE,	//ハードウェアアクセラレータを使用
		nullptr,	//ソフトウェアラスタライザ
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&_swapchain,
		&_device,
		pFeatureLevel,
		&_context);

	 //アンチエイリアシングの設定

	//_swapchain->Release();

	//result = D3D11CreateDevice(nullptr,
	//	D3D_DRIVER_TYPE_HARDWARE,
	//	nullptr,
	//	0,
	//	&pFeatureLevels,
	//	1,
	//	D3D11_SDK_VERSION,
	//	&_device,
	//	pFeatureLevel,
	//	&_context);

	//if (FAILED(result))
	//{
	//	MessageBox(hwnd, "failed D3D11CreateDevice", "Error", MB_OK);
	//	return result;
	//}

	////インターフェースをクエリ
	//IDXGIDevice1* pDxgi = nullptr;
	//result = _device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDxgi);
	//if (FAILED(result))
	//{
	//	MessageBox(hwnd, "failed QueryInterface", "Error", MB_OK);
	//	return result;
	//}

	////Dxgiからアダプタを取得
	//IDXGIAdapter* pAdapter = nullptr;
	//result = pDxgi->GetAdapter(&pAdapter);
	//if (FAILED(result))
	//{
	//	MessageBox(hwnd, "failed GetAdapter", "Error", MB_OK);
	//	return result;
	//}

	////アダプタからファクトリを取得
	//IDXGIFactory* pDxgiFactory = nullptr;
	//pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pDxgiFactory);
	//if (pDxgiFactory == nullptr)
	//{
	//	MessageBox(hwnd, "failed GetFactory", "Error", MB_OK);
	//	return result;
	//}

	////アンチエイリアスの設定
	//DXGI_SAMPLE_DESC sampleDesc;
	//for (int cnt = 0; cnt <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; ++cnt)
	//{
	//	UINT quality;

	//	result = _device->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, cnt, &quality);

	//	if (SUCCEEDED(result))
	//	{
	//		if (0 < quality)
	//		{
	//			sampleDesc.Count = cnt;
	//			sampleDesc.Quality = quality - 1;
	//		}
	//	}
	//}

	////スワップチェインパラメータ設定
	//sd = {};
	//sd.BufferCount = 1;
	//sd.BufferDesc.Width = wc.WindowWidth();
	//sd.BufferDesc.Height = wc.WindowHeight();
	//sd.BufferDesc.RefreshRate.Numerator = 60;
	//sd.BufferDesc.RefreshRate.Denominator = 1;
	//sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//sd.OutputWindow = hwnd;
	//sd.SampleDesc = sampleDesc;
	//sd.Windowed = TRUE;
	//sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//result = pDxgiFactory->CreateSwapChain(_device, &sd, &_swapchain);
	//
	//if (FAILED(result))
	//{
	//	MessageBox(hwnd, "failed createSwapChain", "Error", MB_OK);
	//	return result;
	//}

	//カリングの設定
	D3D11_RASTERIZER_DESC raster_desc = {};
	raster_desc.FillMode = D3D11_FILL_SOLID;	//塗りつぶし
	raster_desc.CullMode = D3D11_CULL_NONE;		//カリングをしない

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOffState);

	raster_desc.FillMode = D3D11_FILL_SOLID;	//塗りつぶし
	raster_desc.CullMode = D3D11_CULL_BACK;		//カリングをしない

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOnState);

	_context->RSSetState(_cullingOnState);

	return result;
}

HRESULT 
DeviceDx11::Reset(WindowControl& wc)
{
	_device->Release();
	_swapchain->Release();
	_context->Release();

	//デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferCount = 1; //バックバッファの数1
	sd.BufferDesc.Width = wc.WindowWidth();
	sd.BufferDesc.Height = wc.WindowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//バックバッファのフォーマット
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = wc.WindowHandle();
	sd.SampleDesc.Count = 1;//サンプリング数 
	sd.Windowed = TRUE;//ウィンドウモード

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0; //使用するフィーチャDirectX11
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;

	//デバイスの作成
	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr,	//既定のアダプタを使用
		D3D_DRIVER_TYPE_HARDWARE,	//ハードウェアアクセラレータを使用
		nullptr,	//ソフトウェアラスタライザ
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&_swapchain,
		&_device,
		pFeatureLevel,
		&_context);

	return result;
}

IDXGISwapChain* 
DeviceDx11::SwapChain()
{
	return _swapchain;
}

ID3D11Device* 
DeviceDx11::Device()
{
	return _device;
}

ID3D11DeviceContext* 
DeviceDx11::Context()
{
	return _context;
}

void 
DeviceDx11::Terminate()
{
	if (_device)
	{
		_device->Release();
	}
	if (_swapchain)
	{
		_swapchain->Release();
	}
	if (_context)
	{
		_context->Release();
	}
}

void 
DeviceDx11::SetCullingFlg(bool flg)
{
	if (flg)
	{
		_context->RSSetState(_cullingOnState);
	}
	else
	{
		_context->RSSetState(_cullingOffState);
	}
}

HWND 
DeviceDx11::WindowHandle() 
{
	return _hwnd; 
}
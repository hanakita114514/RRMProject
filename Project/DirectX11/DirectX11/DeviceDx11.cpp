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

	//カリングの設定
	D3D11_RASTERIZER_DESC raster_desc = {};
	raster_desc.FillMode = D3D11_FILL_SOLID;	//塗りつぶし
	raster_desc.CullMode = D3D11_CULL_NONE;		//カリングをしない

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOffState);

	raster_desc.FillMode = D3D11_FILL_SOLID;	//塗りつぶし
	raster_desc.CullMode = D3D11_CULL_BACK;		//カリングをしない

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOnState);

	_context->RSSetState(_cullingOnState);

	//アルファブレンディングの設定
	ID3D11BlendState* blendstate = nullptr;
	D3D11_BLEND_DESC blenddesc = {};
	blenddesc.AlphaToCoverageEnable = true;
	//blenddesc.AlphaToCoverageEnable = false;
	blenddesc.IndependentBlendEnable = false;
	D3D11_RENDER_TARGET_BLEND_DESC& blrtdesc = blenddesc.RenderTarget[0];
	blrtdesc.BlendEnable = true;
	blrtdesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blrtdesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blrtdesc.BlendOp = D3D11_BLEND_OP_ADD;
	blrtdesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	blrtdesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	blrtdesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blrtdesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	float blendFactor[] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	result = _device->CreateBlendState(&blenddesc, &blendstate);
	_context->OMSetBlendState(blendstate, blendFactor, 0xffffffff);

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

}

HWND 
DeviceDx11::WindowHandle() 
{
	return _hwnd; 
}
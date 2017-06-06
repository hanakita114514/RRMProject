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
	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferCount = 1; //�o�b�N�o�b�t�@�̐�1
	sd.BufferDesc.Width = wc.WindowWidth();
	sd.BufferDesc.Height = wc.WindowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�o�b�N�o�b�t�@�̃t�H�[�}�b�g
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = wc.WindowHandle();
	sd.SampleDesc.Count = 1;//�T���v�����O�� 
	sd.Windowed = TRUE;//�E�B���h�E���[�h

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0; //�g�p����t�B�[�`��DirectX11
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;

	//�f�o�C�X�̍쐬
	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr,	//����̃A�_�v�^���g�p
		D3D_DRIVER_TYPE_HARDWARE,	//�n�[�h�E�F�A�A�N�Z�����[�^���g�p
		nullptr,	//�\�t�g�E�F�A���X�^���C�U
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&_swapchain,
		&_device,
		pFeatureLevel,
		&_context);

	//�J�����O�̐ݒ�
	D3D11_RASTERIZER_DESC raster_desc = {};
	raster_desc.FillMode = D3D11_FILL_SOLID;	//�h��Ԃ�
	raster_desc.CullMode = D3D11_CULL_NONE;		//�J�����O�����Ȃ�

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOffState);

	raster_desc.FillMode = D3D11_FILL_SOLID;	//�h��Ԃ�
	raster_desc.CullMode = D3D11_CULL_BACK;		//�J�����O�����Ȃ�

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOnState);

	_context->RSSetState(_cullingOnState);

	//�A���t�@�u�����f�B���O�̐ݒ�
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

	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferCount = 1; //�o�b�N�o�b�t�@�̐�1
	sd.BufferDesc.Width = wc.WindowWidth();
	sd.BufferDesc.Height = wc.WindowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�o�b�N�o�b�t�@�̃t�H�[�}�b�g
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = wc.WindowHandle();
	sd.SampleDesc.Count = 1;//�T���v�����O�� 
	sd.Windowed = TRUE;//�E�B���h�E���[�h

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0; //�g�p����t�B�[�`��DirectX11
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;

	//�f�o�C�X�̍쐬
	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr,	//����̃A�_�v�^���g�p
		D3D_DRIVER_TYPE_HARDWARE,	//�n�[�h�E�F�A�A�N�Z�����[�^���g�p
		nullptr,	//�\�t�g�E�F�A���X�^���C�U
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
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

	//�f�o�C�X�̍쐬�ƃX���b�v�`�F�C���̐���
	 result = D3D11CreateDeviceAndSwapChain(nullptr,	//����̃A�_�v�^���g�p
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

	 //�A���`�G�C���A�V���O�̐ݒ�

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

	////�C���^�[�t�F�[�X���N�G��
	//IDXGIDevice1* pDxgi = nullptr;
	//result = _device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDxgi);
	//if (FAILED(result))
	//{
	//	MessageBox(hwnd, "failed QueryInterface", "Error", MB_OK);
	//	return result;
	//}

	////Dxgi����A�_�v�^���擾
	//IDXGIAdapter* pAdapter = nullptr;
	//result = pDxgi->GetAdapter(&pAdapter);
	//if (FAILED(result))
	//{
	//	MessageBox(hwnd, "failed GetAdapter", "Error", MB_OK);
	//	return result;
	//}

	////�A�_�v�^����t�@�N�g�����擾
	//IDXGIFactory* pDxgiFactory = nullptr;
	//pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pDxgiFactory);
	//if (pDxgiFactory == nullptr)
	//{
	//	MessageBox(hwnd, "failed GetFactory", "Error", MB_OK);
	//	return result;
	//}

	////�A���`�G�C���A�X�̐ݒ�
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

	////�X���b�v�`�F�C���p�����[�^�ݒ�
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

	//�J�����O�̐ݒ�
	D3D11_RASTERIZER_DESC raster_desc = {};
	raster_desc.FillMode = D3D11_FILL_SOLID;	//�h��Ԃ�
	raster_desc.CullMode = D3D11_CULL_NONE;		//�J�����O�����Ȃ�

	result = _device->CreateRasterizerState(&raster_desc, &_cullingOffState);

	raster_desc.FillMode = D3D11_FILL_SOLID;	//�h��Ԃ�
	raster_desc.CullMode = D3D11_CULL_BACK;		//�J�����O�����Ȃ�

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
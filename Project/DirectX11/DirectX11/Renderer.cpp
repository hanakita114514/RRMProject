#include "Renderer.h"
#include <D3DX11.h>
#include "DeviceDx11.h"
#include "WindowControl.h"


Renderer::Renderer()
{
	for (int i = 0; i < 4; i++)
	{
		_backColor[i] = 0.0f;
	}
	_backColor[3] = 1.0f;
}


Renderer::~Renderer()
{
}

bool 
Renderer::Init()
{
	HRESULT result = S_OK;

	DeviceDx11& dev = DeviceDx11::Instance();
	WindowControl& wc = WindowControl::Instance();


	//�A���t�@�u�����f�B���O�̐ݒ�
	ID3D11BlendState* blendstate = nullptr;
	D3D11_BLEND_DESC blenddesc = {};
	blenddesc.AlphaToCoverageEnable = false;
	//blenddesc.AlphaToCoverageEnable = true;
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
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	result = dev.Device()->CreateBlendState(&blenddesc, &blendstate);
	dev.Context()->OMSetBlendState(blendstate, blendFactor, 0xffffffff);


	//�o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g�r���[(RTV)���쐬
	ID3D11Texture2D* pBack;
	//�o�b�N�o�b�t�@�̃T�[�t�F�C�X���V�F�[�_���\�[�X(�e�N�X�`��)�Ƃ��Ĕ����o��
	result = dev.SwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);

	if (FAILED(result))
	{
		return false;
	}

	//���̃e�N�X�`���������_�[�^�[�Q�b�g�Ƃ���悤�ȃ����_�[�^�[�Q�b�g�r���[���쐬
	result = dev.Device()->CreateRenderTargetView(pBack, nullptr, &_rtv);

	if (FAILED(result))
	{
		return false;
	}

	pBack->Release();

	//�f�v�X�X�e���V���r���[(DSV)���쐬
	//Z�o�b�t�@
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
	if (FAILED(result))
	{
		return false;
	}

	result = dev.Device()->CreateDepthStencilView(_depthTexture2D, nullptr, &_dsv);
	if (FAILED(result))
	{
		return false;
	}

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
	//dev.Context()->OMSetRenderTargets(1, &_rtv, nullptr);

	return true;
}

void 
Renderer::SetZBuffer(bool flag)
{
	DeviceDx11& dev = DeviceDx11::Instance();
	if (flag)
	{
		dev.Context()->OMSetRenderTargets(1, &_rtv, _dsv);
	}
	else
	{
		dev.Context()->OMSetRenderTargets(1, &_rtv, nullptr);
	}
}

void 
Renderer::Clear()
{
	DeviceDx11& dev = DeviceDx11::Instance();

	dev.Context()->ClearRenderTargetView(_rtv, _backColor);

	dev.Context()->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void 
Renderer::BackGroundColor(int red, int green, int blue)
{
	_backColor[0] = (float)red / 255.0f;
	_backColor[1] = (float)green / 255.0f;
	_backColor[2] = (float)blue / 255.0f;
}

void 
Renderer::DefaultBlend()
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	//D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;
	////�A���t�@�u�����f�B���O�̐ݒ�
	//ID3D11BlendState* blendstate = nullptr;
	//D3D11_BLEND_DESC blenddesc = {};
	//blenddesc.AlphaToCoverageEnable = false;
	//blenddesc.IndependentBlendEnable = false;
	//RenderTarget.BlendEnable = false;

	//RenderTarget.SrcBlend = D3D11_BLEND_ONE;
	//RenderTarget.DestBlend = D3D11_BLEND_ZERO;
	//RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	//RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	//RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	//RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	//result = dev.Device()->CreateBlendState(&blenddesc, &blendstate);
	//dev.Context()->OMSetBlendState(blendstate, blendFactor, 0xffffffff);

	//�A���t�@�u�����f�B���O�̐ݒ�
	ID3D11BlendState* blendstate = nullptr;
	D3D11_BLEND_DESC blenddesc = {};
	blenddesc.AlphaToCoverageEnable = false;
	//blenddesc.AlphaToCoverageEnable = true;
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
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	result = dev.Device()->CreateBlendState(&blenddesc, &blendstate);
	dev.Context()->OMSetBlendState(blendstate, blendFactor, 0xffffffff);
}

void 
Renderer::AlignmentBlend()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = true;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

void 
Renderer::AddBlend()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = true;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_ONE;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

void 
Renderer::SubtractBlend()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = true;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_ONE;
	RenderTarget.BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

void
Renderer::MultipleBlendDesc()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = true;
	RenderTarget.SrcBlend = D3D11_BLEND_ZERO;
	RenderTarget.DestBlend = D3D11_BLEND_SRC_COLOR;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

void
Renderer::AlphaBlend(int pal)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	float alpha;
	alpha = (float)pal / 255.0f;

	if (pal > 255)
	{
		alpha = 1.0f;
	}
	else if (pal < 0)
	{
		alpha = 0.0f;
	}

	//�A���t�@�u�����f�B���O�̐ݒ�
	ID3D11BlendState* blendstate = nullptr;
	D3D11_BLEND_DESC blenddesc = {};
	blenddesc.AlphaToCoverageEnable = false;
	blenddesc.IndependentBlendEnable = false;

	D3D11_RENDER_TARGET_BLEND_DESC& blrtdesc = blenddesc.RenderTarget[0];
	blrtdesc.BlendEnable = true;
	blrtdesc.SrcBlend = D3D11_BLEND_BLEND_FACTOR;
	blrtdesc.DestBlend = D3D11_BLEND_INV_BLEND_FACTOR;
	blrtdesc.BlendOp = D3D11_BLEND_OP_ADD;
	blrtdesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	blrtdesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	blrtdesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blrtdesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[] = { alpha, alpha, alpha, alpha };

	result = dev.Device()->CreateBlendState(&blenddesc, &blendstate);
	dev.Context()->OMSetBlendState(blendstate, blendFactor, 0xffffffff);
}
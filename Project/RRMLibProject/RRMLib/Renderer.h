#pragma once

#include "RRMCommon.h"

struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilView;
struct ID3D11BlendState;

class Renderer
{
private:
	//レンダラー
	ID3D11RenderTargetView* _rtv;
	ID3D11Texture2D* _depthTexture2D;	//深度用テクスチャ
	ID3D11DepthStencilView* _dsv;	//深度ビュー

	ID3D11BlendState* _defaultBlend;
	ID3D11BlendState* _alphaBlend;
	ID3D11BlendState* _alignmentBlend;
	ID3D11BlendState* _addBlend;
	ID3D11BlendState* _subtractBlend;
	ID3D11BlendState* _multipleBlend;

	void CreateDefaultBlend();
	void CreateAlignmentBlend();
	void CreateAddBlend();
	void CreateSubtractBlend();
	void CreateMultipleBlend();
	void CreateAlphaBlend();

	Renderer();
	Renderer(const Renderer&);
	Renderer& operator = (const Renderer&);

	float _backColor[4];

public:
	~Renderer();

	static Renderer& Instance()
	{
		static Renderer instance;
		return instance;
	}

	bool Init();

	//Zバッファの設定
	//true 有効 false 無効
	void SetZBuffer(bool flag);

	// 0　〜 255で指定
	void BackGroundColor(int red, int green, int blue);

	void Clear();

	void DefaultBlend();
	void AlignmentBlend();
	void AddBlend();
	void SubtractBlend();
	void MultipleBlend();

	//pal 0 〜 255で指定
	void AlphaBlend(int pal);

};


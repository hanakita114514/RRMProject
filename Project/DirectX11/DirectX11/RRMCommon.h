#pragma once
#include "Vertex.h"

struct ID3D11ShaderResourceView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Buffer;

struct VBufferData2D
{
	XMFLOAT2 luv;		//左上UV
	XMFLOAT2 ruv;		//右上UV
	float width;		//画像の幅
	float height;		//画像の高さ
};

struct DrawingStructure
{
	ID3D11VertexShader* vs;				//頂点シェーダ
	ID3D11PixelShader* ps;				//ピクセルシェーダ
	ID3D11InputLayout* layout;			//レイアウト
	ID3D11Buffer* colorBuffer;			//コンスタントバッファ
	ID3D11ShaderResourceView* texture;	//テクスチャ
	VBufferData2D vertex;				//頂点データ
	int texSlot;						//テクスチャのレジスタ番号
	int topology;						//プリミティブトポロジー
	unsigned int offset;				//オフセット
	unsigned int stride;				//ストライド
	unsigned int drawNum;				//頂点数
};
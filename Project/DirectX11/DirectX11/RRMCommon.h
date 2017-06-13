#pragma once

struct ID3D11ShaderResourceView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Buffer;

struct DrawingStructure
{
	ID3D11VertexShader* vs;				//頂点シェーダ
	ID3D11PixelShader* ps;				//ピクセルシェーダ
	ID3D11InputLayout* layout;			//レイアウト
	ID3D11Buffer* vb;					//頂点バッファ
	ID3D11Buffer* colorBuffer;			//コンスタントバッファ
	ID3D11ShaderResourceView* texture;	//テクスチャ
	int texSlot;						//テクスチャのレジスタ番号
	int topology;	//プリミティブトポロジー
	unsigned int offset;				//オフセット
	unsigned int stride;				//ストライド
	unsigned int drawNum;				//頂点数
};
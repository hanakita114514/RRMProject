#pragma once

#include "Vertex.h"
#include "RRMCommon.h"

class GeometryGraph
{
private:
	ID3D11VertexShader* _vs2d;		//頂点シェーダ
	ID3D11VertexShader* _vs3d;		//頂点シェーダ
	ID3D11PixelShader* _ps;			//ピクセルシェーダ
	ID3D11InputLayout* _layout;		//レイアウト
	ID3D11Buffer* _colorBuf;		//カラー用コンスタントバッファ
	ID3D11Buffer* _vbBox;			//箱描画用頂点バッファ
	ID3D11Buffer* _vbLine;			//線用頂点バッファ
	ID3D11Buffer* _vbCircle;		//円用頂点バッファ


	bool CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps);

public:
	GeometryGraph();
	~GeometryGraph();

	//箱描画
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag);
	//線描画
	void DrawLine(float lx, float ly, float rx, float ry, unsigned int color);
	//点描画
	void DrawPoint(float x, float y, unsigned int color);
	//円描画
	void DrawCircle(float x, float y, float r, unsigned int color, bool fillFlag);
};


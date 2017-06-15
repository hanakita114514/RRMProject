#pragma once

#include <string>
#include "Vertex.h"
#include <map>
#include "RRMCommon.h"

//画像の読み込み、描画を行う
class Graphic
{
private:
	struct TexData
	{
		float height;
		float width;
	};
private:
	ID3D11VertexShader* _vs2d;		//頂点シェーダ
	ID3D11VertexShader* _vs3d;		//頂点シェーダ
	ID3D11PixelShader* _ps;			//ピクセルシェーダ
	ID3D11InputLayout* _layout;		//レイアウト

	std::map<int, TexData> _texData;

	Graphic();
	Graphic(const Graphic&);
	Graphic& operator=(const Graphic&);

	//頂点バッファの生成
	ID3D11Buffer* CreateBuffer2D(float x, float y, float width, float height);

	ID3D11Buffer* CreateBuffer2D(float x, float y, float width, float height, float luvX, float luvY, float ruvX, float ruvY,
		DrawingStructure& ds);
	//CPUから動的書き換え可
	ID3D11Buffer* CreateBuffer2DWrite(float x, float y, float width, float height, DrawingStructure& ds);

	void CreateVertex2D(float x, float y, float width, float height, Vertex2D* vertices, DrawingStructure& ds);

	ID3D11Buffer* CreateBuffer3D(float x, float y, float z, float width, float height);

	HRESULT CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps);

	//シェーダ用に座標をクランプ
	void CrampForShader(float& x, float& y);

public:
	~Graphic();
	static Graphic& Instance()
	{
		static Graphic instance;

		return instance;
	}

	//画像を読み込む
	//戻り値 失敗　-1 成功 それ以外の数値
	int LoadGraph(std::string filePath);

	//ポリゴンを生成
	DrawingStructure CreatePolygon();
	//テクスチャ付きポリゴンの生成
	DrawingStructure CreatePolygon(std::string filePath);

	//画像の分割読み込み
	HRESULT LoadDivGraph(std::string filePath, int allNum,
		int xNum, int yNum, int width, int height, DrawingStructure* handleBuf);

	//画像の描画
	//原点左上から描画
	void DrawGraph(float x, float y, int handle);
	//既に生成されたポリゴンを使って座標左上描画
	void DrawGraph(float x, float y, DrawingStructure& ds);

	//画像の拡縮描画
	// lx ly 左上座標
	// rx ry 右下座標
	// handle 画像ハンドル
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle);
	void DrawExtendGraph(float lx, float ly, float rx, float ry, DrawingStructure ds);

	// 画像の分割描画
	void DrawRectGraph(float destX, float destY,int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag);

	//画像の分割拡縮描画
	void DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag);
};


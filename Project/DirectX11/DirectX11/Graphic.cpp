#include "Graphic.h"
#include <D3DX11.h>
#include <D3D11.h>
#include <d3dx9tex.h>
#include "DeviceDx11.h"
#include "WindowControl.h"
#include "GraphList.h"
#include "Renderer.h"
#include <math.h>

Graphic::Graphic()
{
}


Graphic::~Graphic()
{
	Terminate();
}

bool 
Graphic::Init()
{
	HRESULT hr = S_OK;
	hr = Graphic::CreateShader(_vs2d, _vs3d, _layout, _ps);

	if (FAILED(hr))
	{
		return false;
	}

	DrawingStructure ds;
	_vb = CreateBuffer2DWrite(0, 0, 0, 0, ds);

	return true;
}

void 
Graphic::Terminate()
{
	_vb->Release();
	_vs2d->Release();
	_vs3d->Release();
	_layout->Release();
	_ps->Release();
}

void 
Graphic::CrampForShader(float& x, float& y)
{
	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	x = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	y = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;
}

ID3D11Buffer* 
Graphic::CreateBuffer2D(float x, float y, float width, float height)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D11Buffer* vb;

	Vertex2D vertices[4];

	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = (width / 2) / (wc.WindowWidth() / 2);
	float fh = (height / 2) / (wc.WindowHeight() / 2);

	//左上
	vertices[0].pos.x = fx - fw;
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;

	//右上
	vertices[1].pos.x = fx + fw;
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = 1;
	vertices[1].uv.y = 0;

	//左下
	vertices[2].pos.x = fx - fw;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = 0;
	vertices[2].uv.y = 1;

	//右下
	vertices[3].pos.x = fx + fw;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = 1;
	vertices[3].uv.y = 1;

	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices);
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DEFAULT;
	bufdesc.CPUAccessFlags = 0;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Vertex2D);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	if (FAILED(result))
	{
		return nullptr;
	}

	return vb;
}

ID3D11Buffer* 
Graphic::CreateBuffer2D(float x, float y, float width, float height, float luvX, float luvY, float ruvX, float ruvY,
	DrawingStructure& ds)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D11Buffer* vb;

	Vertex2D vertices[4];

	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = (width / 2) / (wc.WindowWidth() / 2);
	float fh = (height / 2) / (wc.WindowHeight() / 2);

	//左上
	vertices[0].pos.x = fx - fw;
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = luvX;
	vertices[0].uv.y = luvY;

	//右上
	vertices[1].pos.x = fx + fw;
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = ruvX;
	vertices[1].uv.y = luvY;

	//左下
	vertices[2].pos.x = fx - fw;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = luvX;
	vertices[2].uv.y = ruvY;

	//右下
	vertices[3].pos.x = fx + fw;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = ruvX;
	vertices[3].uv.y = ruvY;

	//UVデータを格納
	ds.vertex.luv.x = luvX;
	ds.vertex.luv.y = luvY;
	ds.vertex.ruv.x = ruvX;
	ds.vertex.ruv.y = ruvY;

	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices);
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DYNAMIC;
	bufdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Vertex2D);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	if (FAILED(result))
	{
		return nullptr;
	}

	return vb;
}

ID3D11Buffer*
Graphic::CreateBuffer2DWrite(float x, float y, float width, float height, DrawingStructure& ds)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D11Buffer* vb;

	Vertex2D vertices[4];

	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = (width / 2) / (wc.WindowWidth() / 2);
	float fh = (height / 2) / (wc.WindowHeight() / 2);

	//左上
	vertices[0].pos.x = fx - fw;
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;


	//右上
	vertices[1].pos.x = fx + fw;
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = 1;
	vertices[1].uv.y = 0;

	//左下
	vertices[2].pos.x = fx - fw;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = 0;
	vertices[2].uv.y = 1;

	//右下
	vertices[3].pos.x = fx + fw;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = 1;
	vertices[3].uv.y = 1;

	//左上UV
	ds.vertex.luv = vertices[0].uv;
	//右下UV
	ds.vertex.ruv = vertices[3].uv;

	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices);
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DYNAMIC;
	bufdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Vertex2D);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	if (FAILED(result))
	{
		return nullptr;
	}

	return vb;
}

void 
Graphic::CreateVertex2D(float x, float y, float width, float height, Vertex2D* vertices, DrawingStructure& ds)
{
	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = (width / 2) / (wc.WindowWidth() / 2);
	float fh = (height / 2) / (wc.WindowHeight() / 2);

	//左上
	vertices[0].pos.x = fx - fw;
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = ds.vertex.luv.x;
	vertices[0].uv.y = ds.vertex.luv.y;

	//右上
	vertices[1].pos.x = fx + fw;
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = ds.vertex.ruv.x;
	vertices[1].uv.y = ds.vertex.luv.y;

	//左下
	vertices[2].pos.x = fx - fw;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = ds.vertex.luv.x;
	vertices[2].uv.y = ds.vertex.ruv.y;

	//右下
	vertices[3].pos.x = fx + fw;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = ds.vertex.ruv.x;
	vertices[3].uv.y = ds.vertex.ruv.y;
}

ID3D11Buffer* 
Graphic::CreateBuffer3D(float x, float y, float z, float width, float height)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D11Buffer* vb;

	Vertex2D vertices[4];

	//左上
	vertices[0].pos.x = x - width / 2;
	vertices[0].pos.y = y + height / 2;
	vertices[0].pos.z = z;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;

	//右上
	vertices[1].pos.x = x + width / 2;
	vertices[1].pos.y = y + height / 2;
	vertices[1].pos.z = z;
	vertices[1].uv.x = 1;
	vertices[1].uv.y = 0;

	//左下
	vertices[2].pos.x = x - width / 2;
	vertices[2].pos.y = y - height / 2;
	vertices[2].pos.z = z;
	vertices[2].uv.x = 0;
	vertices[2].uv.y = 1;

	//右下
	vertices[3].pos.x = x + width / 2;
	vertices[3].pos.y = y - height / 2;
	vertices[3].pos.z = z;
	vertices[3].uv.x = 1;
	vertices[3].uv.y = 1;

	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices[0]) * 4;
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DYNAMIC;
	bufdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Vertex2D);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	return vb;
}

HRESULT 
Graphic::CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps)
{
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D10Blob* shader = nullptr;
	ID3D10Blob* shaderError = nullptr;

	//2D頂点シェーダ
	HRESULT result = D3DX11CompileFromFile("2DShader.hlsl",
		nullptr,
		nullptr,
		"VertexShader2D",
		"vs_5_0",
		0,
		0,
		nullptr,
		&shader,
		&shaderError,
		nullptr
	);


	result = dev.Device()->CreateVertexShader(shader->GetBufferPointer(),
		shader->GetBufferSize(),
		nullptr,
		&vs2d);

	char* errmsg;
	if (shaderError != nullptr)
	{
		errmsg = static_cast<char*>(shaderError->GetBufferPointer());
		OutputDebugString(errmsg);
		shaderError->Release();
	}

	shader->Release();

	//3D頂点シェーダ
	result = D3DX11CompileFromFile("2DShader.hlsl",
		nullptr,
		nullptr,
		"VertexShader3D",
		"vs_5_0",
		0,
		0,
		nullptr,
		&shader,
		&shaderError,
		nullptr
	);


	result = dev.Device()->CreateVertexShader(shader->GetBufferPointer(),
		shader->GetBufferSize(),
		nullptr,
		&vs3d);

	if (shaderError != nullptr)
	{
		errmsg = static_cast<char*>(shaderError->GetBufferPointer());
		OutputDebugString(errmsg);
		shaderError->Release();
	}


	//インプットレイアウト
	D3D11_INPUT_ELEMENT_DESC inputElemDescs[] =
	{
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	result = dev.Device()->CreateInputLayout(inputElemDescs,
		sizeof(inputElemDescs) / sizeof(inputElemDescs[0]),
		shader->GetBufferPointer(),
		shader->GetBufferSize(),
		&layout);

	shader->Release();

	//ピクセルシェーダ
	result = D3DX11CompileFromFile("2DShader.hlsl",
		nullptr,
		nullptr,
		"PicturePS",
		"ps_5_0",
		0,
		0,
		nullptr,
		&shader,
		&shaderError,
		nullptr
	);

	result = dev.Device()->CreatePixelShader(shader->GetBufferPointer(),
		shader->GetBufferSize(),
		nullptr,
		&ps);


	return result;
}

int 
Graphic::LoadTexture(std::string filePath)
{
	
	HRESULT result;
	DeviceDx11& dev = DeviceDx11::Instance();

	int handle;

	//テクスチャの読み込み
	ID3D11ShaderResourceView* tex = nullptr;
	result = D3DX11CreateShaderResourceViewFromFile(
		dev.Device(),
		filePath.c_str(),
		nullptr,
		nullptr,
		&tex,
		nullptr);

	handle = (int)tex;

	if (FAILED(result))
	{
		handle = -1;
	}

	TexData data;
	D3DXIMAGE_INFO imageData;

	D3DXGetImageInfoFromFile(filePath.c_str(), &imageData);
	data.height = (float)imageData.Height;
	data.width = (float)imageData.Width;
	_texData[handle] = data;

	return handle;
}

int
Graphic::LoadGraph(std::string filePath)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	DrawingStructure* ds = new DrawingStructure();
	ds->drawNum = 4;
	ds->vs = _vs2d;
	ds->ps = _ps;
	ds->topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	ds->layout = _layout;
	ds->stride = sizeof(Vertex2D);
	ds->offset = 0;

	int handle = LoadTexture(filePath);
	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)handle;
	ds->texSlot = 1;
	ds->texture = texture;

	TexData t = _texData[handle];
	ds->vertex.width = t.width;
	ds->vertex.height = t.height;
	ds->vertex.luv = XMFLOAT2(0, 0);
	ds->vertex.ruv = XMFLOAT2(1, 1);

	return (int)ds;
}

HRESULT 
Graphic::LoadDivGraph(std::string filePath, int allNum,
	int xNum, int yNum, int width, int height, int* handleBuf)
{   
	HRESULT result = S_OK;

	DeviceDx11& dev = DeviceDx11::Instance();

	int handle = LoadTexture(filePath);

	//テクスチャの読み込み
	ID3D11ShaderResourceView* tex = (ID3D11ShaderResourceView*)handle;

	DrawingStructure initDS = {};

	for (int i = 0; i < allNum; i++)
	{
		XMFLOAT2 luv;
		luv.x = (float)((i % xNum) / (float)xNum);
		luv.y = (float)((i / xNum) / (float)yNum);
		XMFLOAT2 ruv;
		ruv.x = (float)(((i % xNum) + 1) / (float)xNum);
		ruv.y = (float)(((i / xNum) + 1) / (float)yNum);

		DrawingStructure* ds = new DrawingStructure();

		//初期化
		//handleBuf[i] = initDS;

		ds->vs = _vs2d;
		ds->ps = _ps;
		ds->layout = _layout;
		ds->texture = tex;
		ds->texSlot = 1;
		ds->offset = 0;
		ds->stride = sizeof(Vertex2D);
		ds->topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		ds->drawNum = 4;
		ds->colorBuffer = nullptr;
		//ds->vb = CreateBuffer2D(0, 0, width, height, luv.x, luv.y, ruv.x, ruv.y, *ds);
		ds->vertex.luv = luv;
		ds->vertex.ruv = ruv;
		ds->vertex.height = height;
		ds->vertex.width = width;
		handleBuf[i] = (int)ds;
	}

	TexData data;
	D3DXIMAGE_INFO imageData;

	D3DXGetImageInfoFromFile(filePath.c_str(), &imageData);
	data.height = (float)imageData.Height;
	data.width = (float)imageData.Width;
	_texData[handle] = data;

	return result;
}

DrawingStructure
Graphic::CreatePolygon()
{
	DrawingStructure ds = {};
	ds.drawNum = 4;
	ds.vs = _vs2d;
	ds.ps = _ps;
	ds.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	ds.layout = _layout;
	ds.stride = sizeof(Vertex2D);
	ds.offset = 0;

	return ds;
}

//void
//Graphic::DrawGraph(float x, float y, int handle)
//{
//	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)handle;
//	TexData t = _texData[handle];
//	WindowControl& wc = WindowControl::Instance();
//	//ID3D11Buffer* vBuffer = CreateBuffer2D(x, y, t.width, t.height);
//	ID3D11Buffer* vBuffer = CreateBuffer2D(x + t.width / 2, y + t.height / 2, t.width, t.height);
//
//	DeviceDx11& dev = DeviceDx11::Instance();
//	unsigned int offset = 0;
//	unsigned int stride = sizeof(Vertex2D);
//
//	//描画構造体に格納
//	//DrawingStructure ds = {};
//	//ds.vs = _vs2d;
//	//ds.ps = _ps;
//	//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
//	//ds.layout = _layout;
//	//ds.texSlot = 1;
//	//ds.texture = texture;
//	//ds.stride = sizeof(Vertex2D);
//	//ds.offset = 0;
//	//ds.drawNum = 4;
//	//ds.vb = vBuffer;
//
//	//セッターはひとまとめにする
//	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
//	dev.Context()->PSSetShader(_ps, nullptr, 0);
//	dev.Context()->IASetInputLayout(_layout);
//	dev.Context()->PSSetShaderResources(0, 1, &texture);
//	dev.Context()->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
//
//	dev.Context()->Draw(4, 0);
//	
//	//使用した後リリース
//	vBuffer->Release();
//
//}

void
Graphic::DrawGraph(float x, float y, int handle, bool transFlag)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	DrawingStructure* ds = (DrawingStructure*)handle;

	Vertex2D vertex[4];
	CreateVertex2D(x + ds->vertex.width / 2, y + ds->vertex.height / 2, ds->vertex.width, ds->vertex.height, vertex, *ds);

	WindowControl& wc = WindowControl::Instance();	

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertex, sizeof(Vertex2D) * 4);
	dev.Context()->Unmap(_vb, 0);

	dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)ds->topology);
	dev.Context()->VSSetShader(ds->vs, nullptr, 0);
	dev.Context()->PSSetShader(ds->ps, nullptr, 0);
	dev.Context()->IASetInputLayout(ds->layout);
	dev.Context()->PSSetShaderResources(0, ds->texSlot, &ds->texture);
	dev.Context()->IASetVertexBuffers(0, 1, &_vb, &ds->stride, &ds->offset);

	dev.Context()->Draw(ds->drawNum, 0);
}

//
//// 画像の分割描画
//void
//Graphic::DrawRectGraph(float destX, float destY, int srcX, int srcY,
//	int width, int height, int graphHandle, bool transFlag, bool turnFlag)
//{
//	HRESULT result;
//	DeviceDx11& dev = DeviceDx11::Instance();
//	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)graphHandle;
//	TexData t = _texData[graphHandle];
//
//	//バッファの生成
//	//ID3D11Buffer* vBuffer = CreateBuffer2D(0, 0, 0, t.width, t.height);
//
//	ID3D11Buffer* vb;
//
//	Vertex2D vertices[4];
//
//	WindowControl& wc = WindowControl::Instance();
//
//	//ウィンドウ座標系を-1～1にクランプ
//	float x = destX + width / 2;
//	float y = destY + height / 2;
//	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
//	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;
//
//	float fw = ((float)width / 2) / ((float)wc.WindowWidth() / 2);
//	float fh = ((float)height / 2) / ((float)wc.WindowHeight() / 2);
//
//
//	//左上
//	vertices[0].pos.x = (fx - fw);
//	vertices[0].pos.y = fy + fh;
//	vertices[0].pos.z = 0;
//	vertices[0].uv.x = srcX / t.width;
//	vertices[0].uv.y = srcY / t.height;
//
//	//右上
//	vertices[1].pos.x = (fx + fw);
//	vertices[1].pos.y = fy + fh;
//	vertices[1].pos.z = 0;
//	vertices[1].uv.x = (width + srcX) / t.width;
//	vertices[1].uv.y = srcY / t.height;
//
//	//左下
//	vertices[2].pos.x = (fx - fw);
//	vertices[2].pos.y = fy - fh;
//	vertices[2].pos.z = 0;
//	vertices[2].uv.x = srcX / t.width;;
//	vertices[2].uv.y = (height + srcY) / t.height;
//
//	//右下
//	vertices[3].pos.x = (fx + fw);
//	vertices[3].pos.y = fy - fh;
//	vertices[3].pos.z = 0;
//	vertices[3].uv.x = (width + srcX) / t.width;
//	vertices[3].uv.y = (height + srcY) / t.height;
//
//	if (turnFlag)
//	{
//		vertices[0].uv.x = (width + srcX) / t.width;
//		vertices[0].uv.y = srcY / t.height;
//
//		vertices[1].uv.x = srcX / t.width;
//		vertices[1].uv.y = srcY / t.height;
//
//		vertices[2].uv.x = (width + srcX) / t.width;
//		vertices[2].uv.y = (height + srcY) / t.height;
//
//		vertices[3].uv.x = srcX / t.width;;
//		vertices[3].uv.y = (height + srcY) / t.height;
//	}
//
//
//	//頂点バッファの作成
//	D3D11_BUFFER_DESC bufdesc = {};
//	bufdesc.ByteWidth = sizeof(vertices[0]) * 4;
//	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bufdesc.Usage = D3D11_USAGE_DEFAULT;
//	bufdesc.CPUAccessFlags = 0;
//	bufdesc.MiscFlags = 0;
//	bufdesc.StructureByteStride = sizeof(Vertex2D);
//
//	D3D11_SUBRESOURCE_DATA subdata = {};
//	subdata.pSysMem = &vertices[0];
//
//	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);
//
//	////描画構造体に格納
//	//DrawingStructure ds = {};
//	//ds.vs = _vs2d;
//	//ds.ps = _ps;
//	//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
//	//ds.layout = _layout;
//	//ds.texSlot = 1;
//	//ds.texture = texture;
//	//ds.stride = sizeof(Vertex2D);
//	//ds.offset = 0;
//	//ds.drawNum = 4;
//	//ds.vb = vb;
//
//	unsigned int offset = 0;
//	unsigned int stride = sizeof(Vertex2D);
//
//	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
//	dev.Context()->PSSetShader(_ps, nullptr, 0);
//	dev.Context()->IASetInputLayout(_layout);
//	dev.Context()->PSSetShaderResources(0, 1, &texture);
//	dev.Context()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
//
//	dev.Context()->Draw(4, 0);
//	vb->Release();
//
//}

void 
Graphic::DrawRectGraph(float destX, float destY, int srcX, int srcY,
	int width, int height, int graphHandle, bool transFlag, bool turnFlag)
{
	HRESULT result;
	DeviceDx11& dev = DeviceDx11::Instance();
	DrawingStructure* ds = (DrawingStructure*)graphHandle;
	int texHandle = (int)ds->texture;
	TexData t = _texData[texHandle];

	Vertex2D vertices[4];

	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	float x = destX + width / 2;
	float y = destY + height / 2;
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = ((float)width / 2) / ((float)wc.WindowWidth() / 2);
	float fh = ((float)height / 2) / ((float)wc.WindowHeight() / 2);


	//左上
	vertices[0].pos.x = (fx - fw);
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = srcX / ds->vertex.width;
	vertices[0].uv.y = srcY / ds->vertex.height;

	//右上
	vertices[1].pos.x = (fx + fw);
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = (width + srcX) / ds->vertex.width;
	vertices[1].uv.y = srcY / ds->vertex.height;

	//左下
	vertices[2].pos.x = (fx - fw);
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = srcX / ds->vertex.width;;
	vertices[2].uv.y = (height + srcY) / ds->vertex.height;

	//右下
	vertices[3].pos.x = (fx + fw);
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = (width + srcX) / ds->vertex.width;
	vertices[3].uv.y = (height + srcY) / ds->vertex.height;

	if (turnFlag)
	{
		vertices[0].uv.x = (width + srcX) / ds->vertex.width;
		vertices[0].uv.y = srcY / ds->vertex.height;

		vertices[1].uv.x = srcX / ds->vertex.width;
		vertices[1].uv.y = srcY / ds->vertex.height;

		vertices[2].uv.x = (width + srcX) / ds->vertex.width;
		vertices[2].uv.y = (height + srcY) / ds->vertex.height;

		vertices[3].uv.x = srcX / ds->vertex.width;;
		vertices[3].uv.y = (height + srcY) / ds->vertex.height;
	}

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertices, sizeof(Vertex2D) * 4);
	dev.Context()->Unmap(_vb, 0);


	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)ds->topology);
	dev.Context()->VSSetShader(ds->vs, nullptr, 0);
	dev.Context()->PSSetShader(ds->ps, nullptr, 0);
	dev.Context()->IASetInputLayout(ds->layout);
	dev.Context()->PSSetShaderResources(0, 1, &ds->texture);
	dev.Context()->IASetVertexBuffers(0, 1, &_vb, &ds->stride, &ds->offset);

	dev.Context()->Draw(ds->drawNum, 0);
}

//void
//Graphic::DrawExtendGraph(float lx, float ly, float rx, float ry, int handle)
//{
//	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)handle;
//	TexData t = _texData[handle];
//	WindowControl& wc = WindowControl::Instance();
//	//ID3D11Buffer* vBuffer = CreateBuffer2D(x, y, t.width, t.height);
//
//	float width = rx - lx;
//	float height = ry - ly;
//
//
//	ID3D11Buffer* vBuffer = CreateBuffer2D(lx + width / 2, ly + height / 2, width, height);
//
//	DeviceDx11& dev = DeviceDx11::Instance();
//	unsigned int offset = 0;
//	unsigned int stride = sizeof(Vertex2D);
//
//	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
//	dev.Context()->PSSetShader(_ps, nullptr, 0);
//	dev.Context()->IASetInputLayout(_layout);
//	dev.Context()->PSSetShaderResources(0, 1, &texture);
//	dev.Context()->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
//
//	dev.Context()->Draw(4, 0);
//	vBuffer->Release();
//
//	////描画構造体に格納
//	//DrawingStructure ds = {};
//	//ds.vs = _vs2d;
//	//ds.ps = _ps;
//	//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
//	//ds.layout = _layout;
//	//ds.texSlot = 1;
//	//ds.texture = texture;
//	//ds.stride = sizeof(Vertex2D);
//	//ds.offset = 0;
//	//ds.drawNum = 4;
//	//ds.vb = vBuffer;
//}

void 
Graphic::DrawExtendGraph(float lx, float ly, float rx, float ry, int handle, bool transFlag, bool turnFlag)
{
	WindowControl& wc = WindowControl::Instance();
	HRESULT result;
	DeviceDx11& dev = DeviceDx11::Instance();

	DrawingStructure* ds = (DrawingStructure*)handle;

	Vertex2D vertices[4];

	//ウィンドウ座標系を-1～1にクランプ
	float w = rx - lx;
	float h = ry - ly;

	float x = lx + w / 2;
	float y = ly + h / 2;
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = ((float)w / 2) / ((float)wc.WindowWidth() / 2);
	float fh = ((float)h / 2) / ((float)wc.WindowHeight() / 2);


	//左上
	vertices[0].pos.x = (fx - fw);
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;

	//右上
	vertices[1].pos.x = (fx + fw);
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = 1;
	vertices[1].uv.y = 0;

	//左下
	vertices[2].pos.x = (fx - fw);
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = 0;
	vertices[2].uv.y = 1;

	//右下
	vertices[3].pos.x = (fx + fw);
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = 1;
	vertices[3].uv.y = 1;

	if (turnFlag)
	{
		vertices[0].uv.x = 1;
		vertices[0].uv.y = 0;

		vertices[1].uv.x = 0;
		vertices[1].uv.y = 0;

		vertices[2].uv.x = 1;
		vertices[2].uv.y = 1;

		vertices[3].uv.x = 0;
		vertices[3].uv.y = 1;
	}


	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertices, sizeof(Vertex2D) * 4);
	dev.Context()->Unmap(_vb, 0);


	dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)ds->topology);
	dev.Context()->VSSetShader(ds->vs, nullptr, 0);
	dev.Context()->PSSetShader(ds->ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->PSSetShaderResources(0, 1, &ds->texture);
	dev.Context()->IASetVertexBuffers(0, 1, &_vb, &ds->stride, &ds->offset);

	dev.Context()->Draw(ds->drawNum, 0);
}

//void
//Graphic::DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY, int srcX, int srcY,
//	int width, int height, int graphHandle, bool transFlag, bool turnFlag)
//{
//	HRESULT result;
//	DeviceDx11& dev = DeviceDx11::Instance();
//	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)graphHandle;
//	TexData t = _texData[graphHandle];
//
//	//バッファの生成
//	//ID3D11Buffer* vBuffer = CreateBuffer2D(0, 0, 0, t.width, t.height);
//
//	ID3D11Buffer* vb;
//
//	Vertex2D vertices[4];
//
//	WindowControl& wc = WindowControl::Instance();
//
//	//ウィンドウ座標系を-1～1にクランプ
//	float w = destRX - destLX;
//	float h = destRY - destLY;
//
//	float x = destLX + w / 2;
//	float y = destLY + h / 2;
//	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
//	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;
//
//	float fw = ((float)w / 2) / ((float)wc.WindowWidth() / 2);
//	float fh = ((float)h / 2) / ((float)wc.WindowHeight() / 2);
//
//
//	//左上
//	vertices[0].pos.x = (fx - fw);
//	vertices[0].pos.y = fy + fh;
//	vertices[0].pos.z = 0;
//	vertices[0].uv.x = srcX / t.width;
//	vertices[0].uv.y = srcY / t.height;
//
//	//右上
//	vertices[1].pos.x = (fx + fw);
//	vertices[1].pos.y = fy + fh;
//	vertices[1].pos.z = 0;
//	vertices[1].uv.x = (width + srcX) / t.width;
//	vertices[1].uv.y = srcY / t.height;
//
//	//左下
//	vertices[2].pos.x = (fx - fw);
//	vertices[2].pos.y = fy - fh;
//	vertices[2].pos.z = 0;
//	vertices[2].uv.x = srcX / t.width;;
//	vertices[2].uv.y = (height + srcY) / t.height;
//
//	//右下
//	vertices[3].pos.x = (fx + fw);
//	vertices[3].pos.y = fy - fh;
//	vertices[3].pos.z = 0;
//	vertices[3].uv.x = (width + srcX) / t.width;
//	vertices[3].uv.y = (height + srcY) / t.height;
//
//	if (turnFlag)
//	{
//		vertices[0].uv.x = (width + srcX) / t.width;
//		vertices[0].uv.y = srcY / t.height;
//
//		vertices[1].uv.x = srcX / t.width;
//		vertices[1].uv.y = srcY / t.height;
//
//		vertices[2].uv.x = (width + srcX) / t.width;
//		vertices[2].uv.y = (height + srcY) / t.height;
//
//		vertices[3].uv.x = srcX / t.width;;
//		vertices[3].uv.y = (height + srcY) / t.height;
//	}
//
//	//頂点バッファの作成
//	D3D11_BUFFER_DESC bufdesc = {};
//	bufdesc.ByteWidth = sizeof(vertices[0]) * 4;
//	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bufdesc.Usage = D3D11_USAGE_DEFAULT;
//	bufdesc.CPUAccessFlags = 0;
//	bufdesc.MiscFlags = 0;
//	bufdesc.StructureByteStride = sizeof(Vertex2D);
//
//	D3D11_SUBRESOURCE_DATA subdata = {};
//	subdata.pSysMem = &vertices[0];
//
//	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);
//
//	unsigned int offset = 0;
//	unsigned int stride = sizeof(Vertex2D);
//
//	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
//	dev.Context()->PSSetShader(_ps, nullptr, 0);
//	dev.Context()->IASetInputLayout(_layout);
//	dev.Context()->PSSetShaderResources(0, 1, &texture);
//	dev.Context()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
//
//	dev.Context()->Draw(4, 0);
//	vb->Release();
//
//
//	////描画構造体に格納
//	//DrawingStructure ds = {};
//	//ds.vs = _vs2d;
//	//ds.ps = _ps;
//	//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
//	//ds.layout = _layout;
//	//ds.texSlot = 1;
//	//ds.texture = texture;
//	//ds.stride = sizeof(Vertex2D);
//	//ds.offset = 0;
//	//ds.drawNum = 4;
//	//ds.vb = vb;
//
//}

void 
Graphic::DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY, int srcX, int srcY,
	int width, int height, int graphHandle, bool transFlag, bool turnFlag)
{
	HRESULT result;
	DeviceDx11& dev = DeviceDx11::Instance();

	Vertex2D vertices[4];

	WindowControl& wc = WindowControl::Instance();

	DrawingStructure* ds = (DrawingStructure*)graphHandle;

	//ウィンドウ座標系を-1～1にクランプ
	float w = destRX - destLX;
	float h = destRY - destLY;

	float x = destLX + w / 2;
	float y = destLY + h / 2;
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = ((float)w / 2) / ((float)wc.WindowWidth() / 2);
	float fh = ((float)h / 2) / ((float)wc.WindowHeight() / 2);


	//左上
	vertices[0].pos.x = (fx - fw);
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = srcX / ds->vertex.width;
	vertices[0].uv.y = srcY / ds->vertex.height;

	//右上
	vertices[1].pos.x = (fx + fw);
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = (width + srcX) / ds->vertex.width;
	vertices[1].uv.y = srcY / ds->vertex.height;

	//左下
	vertices[2].pos.x = (fx - fw);
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = srcX / ds->vertex.width;;
	vertices[2].uv.y = (height + srcY) / ds->vertex.height;

	//右下
	vertices[3].pos.x = (fx + fw);
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = (width + srcX) / ds->vertex.width;
	vertices[3].uv.y = (height + srcY) / ds->vertex.height;

	if (turnFlag)
	{
		vertices[0].uv.x = (width + srcX) / ds->vertex.width;
		vertices[0].uv.y = srcY / ds->vertex.height;

		vertices[1].uv.x = srcX / ds->vertex.width;
		vertices[1].uv.y = srcY / ds->vertex.height;

		vertices[2].uv.x = (width + srcX) / ds->vertex.width;
		vertices[2].uv.y = (height + srcY) / ds->vertex.height;

		vertices[3].uv.x = srcX / ds->vertex.width;;
		vertices[3].uv.y = (height + srcY) / ds->vertex.height;
	}


	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertices, sizeof(Vertex2D) * 4);
	dev.Context()->Unmap(_vb, 0);

	dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)ds->topology);
	dev.Context()->VSSetShader(ds->vs, nullptr, 0);
	dev.Context()->PSSetShader(ds->ps, nullptr, 0);
	dev.Context()->IASetInputLayout(ds->layout);
	dev.Context()->PSSetShaderResources(0, 1, &ds->texture);
	dev.Context()->IASetVertexBuffers(0, 1, &_vb, &ds->stride, &ds->offset);

	dev.Context()->Draw(ds->drawNum, 0);
}

void 
Graphic::DeleteGraph(int handle)
{
	DrawingStructure* ds = (DrawingStructure*)handle;
	ds->texture->Release();
	delete(ds);
	ds = nullptr;
}

void 
Graphic::DrawRotaGraphProt(float x, float y, double angle, int graphHandle, bool transFlag, bool turnFlag)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	DrawingStructure* ds = (DrawingStructure*)graphHandle;

	Vertex2D vertex[4];

	float fx = x - ds->vertex.width / 2;
	float fy = y - ds->vertex.height / 2;

	float rotaX = fx * cos(angle) - fy * sin(angle);
	float rotaY = fx * sin(angle) - fy * cos(angle);

	CrampForShader(rotaX, rotaY);

	//左上
	vertex[0].pos.x = rotaX;
	vertex[0].pos.y = rotaY;
	vertex[0].pos.z = 0;
	vertex[0].uv.x = ds->vertex.luv.x;
	vertex[0].uv.y = ds->vertex.luv.y;

	fx = x + ds->vertex.width / 2;

	rotaX = fx * cos(angle) - fy * sin(angle);
	rotaY = fx * sin(angle) - fy * cos(angle);

	CrampForShader(rotaX, rotaY);

	//右上
	vertex[1].pos.x = rotaX;
	vertex[1].pos.y = rotaY;
	vertex[1].pos.z = 0;
	vertex[1].uv.x = ds->vertex.ruv.x;
	vertex[1].uv.y = ds->vertex.luv.y;

	fx = x - ds->vertex.width / 2;
	fy = y + ds->vertex.height / 2;

	rotaX = fx * cos(angle) - fy * sin(angle);
	rotaY = fx * sin(angle) - fy * cos(angle);

	CrampForShader(rotaX, rotaY);

	//左下
	vertex[2].pos.x = rotaX;
	vertex[2].pos.y = rotaY;
	vertex[2].pos.z = 0;
	vertex[2].uv.x = ds->vertex.luv.x;
	vertex[2].uv.y = ds->vertex.ruv.y;

	fx = x + ds->vertex.width / 2;

	rotaX = fx * cos(angle) - fy * sin(angle);
	rotaY = fx * sin(angle) - fy * cos(angle);

	CrampForShader(rotaX, rotaY);

	//右下
	vertex[3].pos.x = rotaX;
	vertex[3].pos.y = rotaY;
	vertex[3].pos.z = 0;
	vertex[3].uv.x = ds->vertex.ruv.x;
	vertex[3].uv.y = ds->vertex.ruv.y;

	WindowControl& wc = WindowControl::Instance();

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertex, sizeof(Vertex2D) * 4);
	dev.Context()->Unmap(_vb, 0);

	dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)ds->topology);
	dev.Context()->VSSetShader(ds->vs, nullptr, 0);
	dev.Context()->PSSetShader(ds->ps, nullptr, 0);
	dev.Context()->IASetInputLayout(ds->layout);
	dev.Context()->PSSetShaderResources(0, ds->texSlot, &ds->texture);
	dev.Context()->IASetVertexBuffers(0, 1, &_vb, &ds->stride, &ds->offset);

	dev.Context()->Draw(ds->drawNum, 0);
}

void 
Graphic::DrawRotaGraph(float x, float y, double angle, int graphHandle, bool transFlag, bool turnFlag)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	DrawingStructure* ds = (DrawingStructure*)graphHandle;

	Vertex2D vertex[4];

	float fx = 0 - (ds->vertex.width / 2);
	float fy = 0 - (ds->vertex.height / 2);

	float rotaX = fx * cos(angle) - fy * sin(angle) + x;
	float rotaY = fx * sin(angle) + fy * cos(angle) + y;

	CrampForShader(rotaX, rotaY);

	//左上
	vertex[0].pos.x = rotaX;
	vertex[0].pos.y = rotaY;
	vertex[0].pos.z = 0;
	vertex[0].uv.x = ds->vertex.luv.x;
	vertex[0].uv.y = ds->vertex.luv.y;

	fx = 0 + (ds->vertex.width / 2);

	rotaX = fx * cos(angle) - fy * sin(angle) + x;
	rotaY = fx * sin(angle) + fy * cos(angle) + y;

	CrampForShader(rotaX, rotaY);

	//右上
	vertex[1].pos.x = rotaX;
	vertex[1].pos.y = rotaY;
	vertex[1].pos.z = 0;
	vertex[1].uv.x = ds->vertex.ruv.x;
	vertex[1].uv.y = ds->vertex.luv.y;

	fx = 0 - (ds->vertex.width / 2);
	fy = 0 + (ds->vertex.height / 2);

	rotaX = fx * cos(angle) - fy * sin(angle) + x;
	rotaY = fx * sin(angle) + fy * cos(angle) + y;

	CrampForShader(rotaX, rotaY);

	//左下
	vertex[2].pos.x = rotaX;
	vertex[2].pos.y = rotaY;
	vertex[2].pos.z = 0;
	vertex[2].uv.x = ds->vertex.luv.x;
	vertex[2].uv.y = ds->vertex.ruv.y;

	fx = 0 + (ds->vertex.width / 2);

	rotaX = fx * cos(angle) - fy * sin(angle) + x;
	rotaY = fx * sin(angle) + fy * cos(angle) + y;

	CrampForShader(rotaX, rotaY);

	//右下
	vertex[3].pos.x = rotaX;
	vertex[3].pos.y = rotaY;
	vertex[3].pos.z = 0;
	vertex[3].uv.x = ds->vertex.ruv.x;
	vertex[3].uv.y = ds->vertex.ruv.y;

	WindowControl& wc = WindowControl::Instance();

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertex, sizeof(Vertex2D) * 4);
	dev.Context()->Unmap(_vb, 0);

	dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)ds->topology);
	dev.Context()->VSSetShader(ds->vs, nullptr, 0);
	dev.Context()->PSSetShader(ds->ps, nullptr, 0);
	dev.Context()->IASetInputLayout(ds->layout);
	dev.Context()->PSSetShaderResources(0, ds->texSlot, &ds->texture);
	dev.Context()->IASetVertexBuffers(0, 1, &_vb, &ds->stride, &ds->offset);

	dev.Context()->Draw(ds->drawNum, 0);
}
#include "GeometryGraph.h"
#include <D3DX11.h>
#include <D3D11.h>
#include "DeviceDx11.h"
#include "WindowControl.h"
#include "Vertex.h"
#include <math.h>

static const double PI = 3.141592f;

GeometryGraph::GeometryGraph()
{
}


GeometryGraph::~GeometryGraph()
{
	Terminate();
}

ID3D11Buffer* CreateVertexBufferBox()
{
	HRESULT hr = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();
	ID3D11Buffer* vb;

	const int vertexNum = 5;

	//頂点バッファの作成
	Vertex2D vertices[vertexNum];

	for (int i = 0; i < vertexNum; i++)
	{
		vertices[i].pos.x = 0;
		vertices[i].pos.y = 0;
		vertices[i].pos.z = 0;
		vertices[i].uv.x = 0;
		vertices[i].uv.y = 0;
	}

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

	hr = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	return vb;
}

ID3D11Buffer* CreateVertexBufferLine()
{
	HRESULT hr = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();
	ID3D11Buffer* vb;

	const int vertexNum = 2;

	//頂点バッファの作成
	Vertex2D vertices[vertexNum];

	for (int i = 0; i < vertexNum; i++)
	{
		//左上
		vertices[i].pos.x = 0;
		vertices[i].pos.y = 0;
		vertices[i].pos.z = 0;
		vertices[i].uv.x = 0;
		vertices[i].uv.y = 0;
	}

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

	hr = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	return vb;
}

ID3D11Buffer* CreateVertexBufferCircle()
{
	HRESULT hr = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();
	ID3D11Buffer* vb;

	const int divNum = 512;

	Vertex2D vertices[divNum];

	WindowControl& wc = WindowControl::Instance();

	for (int i = 0; i < divNum; i++)
	{
		vertices[i].pos.x = 0;
		vertices[i].pos.y = 0;
		vertices[i].pos.z = 0;
		vertices[i].uv.x = 0;
		vertices[i].uv.y = 0;
	}

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

	hr = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	return vb;
}



bool 
GeometryGraph::Init()
{
	DeviceDx11& dev = DeviceDx11::Instance();

	HRESULT hr = CreateShader(_vs2d, _vs3d, _layout, _ps);


	if (FAILED(hr))
	{
		return false;
	}

	unsigned int color = 0xffffffff;
	//カラー用コンスタントバッファの生成
	D3D11_BUFFER_DESC colorBufferDesc = {};
	colorBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	colorBufferDesc.ByteWidth = sizeof(unsigned int) + (16 - sizeof(unsigned int) % 16) % 16;
	colorBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	colorBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA mbufsub = {};
	mbufsub.pSysMem = &color;

	hr = dev.Device()->CreateBuffer(&colorBufferDesc, &mbufsub, &_colorBuf);

	if (FAILED(hr))
	{
		return false;
	}

	dev.Context()->PSSetConstantBuffers(1, 1, &_colorBuf);


	//箱頂点バッファの作成
	_vbBox = CreateVertexBufferBox();

	//線用
	_vbLine = CreateVertexBufferLine();

	//円用
	_vbCircle = CreateVertexBufferCircle();

	return true;

}

void
GeometryGraph::Terminate()
{
	_vbBox->Release();
	_vbLine->Release();
	_vbCircle->Release();
	_vs2d->Release();
	_vs3d->Release();
	_ps->Release();
	_layout->Release();
	_colorBuf->Release();
}

bool 
GeometryGraph::CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps)
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

	if (FAILED(result))
	{
		return false;
	}


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

	if (FAILED(result))
	{
		return false;
	}

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

	if (FAILED(result))
	{
		return false;
	}


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

	if (FAILED(result))
	{
		return false;
	}

	//ピクセルシェーダ
	result = D3DX11CompileFromFile("2DShader.hlsl",
		nullptr,
		nullptr,
		"GeometryPS",
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

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void
GeometryGraph::DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	Vertex2D vertices[5];

	WindowControl& wc = WindowControl::Instance();

	float width = rx - lx;
	float height = ry - ly;

	//ウィンドウ座標系を-1～1にクランプ
	float fx = (lx - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((ly - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = (width) / (wc.WindowWidth() / 2);
	float fh = (height) / (wc.WindowHeight() / 2);

	//左上
	vertices[0].pos.x = fx;
	vertices[0].pos.y = fy;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;

	//右上
	vertices[1].pos.x = fx + fw;
	vertices[1].pos.y = fy;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = 1;
	vertices[1].uv.y = 0;

	//右下
	vertices[2].pos.x = fx + fw;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = 1;
	vertices[2].uv.y = 1;

	//左下
	vertices[3].pos.x = fx;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = 0;
	vertices[3].uv.y = 1;

	//左上
	vertices[4].pos.x = fx;
	vertices[4].pos.y = fy;
	vertices[4].pos.z = 0;
	vertices[4].uv.x = 0;
	vertices[4].uv.y = 0;

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_colorBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, &color, sizeof(unsigned int));
	dev.Context()->Unmap(_colorBuf, 0);

	mappedsub = {};
	result = dev.Context()->Map(_vbBox, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertices, sizeof(Vertex2D) * 5);
	dev.Context()->Unmap(_vbBox, 0);

	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	if (fillFlag)
	{
		dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	else
	{
		dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}

	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->IASetVertexBuffers(0, 1, &_vbBox, &stride, &offset);

	dev.Context()->Draw(5, 0);
}

void
GeometryGraph::DrawLine(float lx, float ly, float rx, float ry, unsigned int color)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	Vertex2D vertices[2];

	WindowControl& wc = WindowControl::Instance();

	float width = rx - lx;
	float height = ry - ly;

	//ウィンドウ座標系を-1～1にクランプ
	float fx = (lx - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((ly - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = (width) / (wc.WindowWidth() / 2);
	float fh = (height) / (wc.WindowHeight() / 2);

	//左上
	vertices[0].pos.x = fx;
	vertices[0].pos.y = fy;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;

	//右上
	vertices[1].pos.x = fx + fw;
	vertices[1].pos.y = fy - fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = 1;
	vertices[1].uv.y = 0;


	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_colorBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, &color, sizeof(unsigned int));
	dev.Context()->Unmap(_colorBuf, 0);

	mappedsub = {};
	result = dev.Context()->Map(_vbLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertices, sizeof(Vertex2D) * 2);
	dev.Context()->Unmap(_vbLine, 0);

	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->IASetVertexBuffers(0, 1, &_vbLine, &stride, &offset);

	dev.Context()->Draw(2, 0);

	//DrawingStructure ds = {};
	//ds.vs = _vs2d;
	//ds.ps = _ps;
	//ds.layout = _layout;
	//ds.texture = nullptr;
	//ds.vb = vb;
	//ds.offset = 0;
	//ds.drawNum = 2;
	//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	//ds.colorBuffer = colorBuf;
	//ds.stride = sizeof(Vertex2D);
}

void
GeometryGraph::DrawPoint(float x, float y, unsigned int color)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D11Buffer* vb;

	Vertex2D vertices[2];

	WindowControl& wc = WindowControl::Instance();


	//ウィンドウ座標系を-1～1にクランプ
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	//左上
	vertices[0].pos.x = fx;
	vertices[0].pos.y = fy;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = 0;
	vertices[0].uv.y = 0;


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

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_colorBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, &color, sizeof(unsigned int));
	dev.Context()->Unmap(_colorBuf, 0);

	//unsigned int offset = 0;
	//unsigned int stride = sizeof(Vertex2D);

	//dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	//dev.Context()->PSSetShader(_ps, nullptr, 0);
	//dev.Context()->IASetInputLayout(_layout);
	////dev.Context()->PSSetShaderResources(0, 1, &texture);
	//dev.Context()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

	//dev.Context()->Draw(1, 0);

	//DrawingStructure ds = {};
	//ds.vs = _vs2d;
	//ds.ps = _ps;
	//ds.layout = _layout;
	//ds.texture = nullptr;
	//ds.vb = vb;
	//ds.offset = 0;
	//ds.drawNum = 1;
	//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	//ds.colorBuffer = colorBuf;
	//ds.stride = sizeof(Vertex2D);

}

void
GeometryGraph::DrawCircle(float x, float y, float r, unsigned int color, bool fillFlag)
{
	HRESULT result = S_OK;
	DeviceDx11& dev = DeviceDx11::Instance();

	ID3D11Buffer* vb;

	const int divNum = 512;

	Vertex2D vertices[divNum];

	WindowControl& wc = WindowControl::Instance();


	//ウィンドウ座標系を-1～1にクランプ
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	for (int i = 0; i < divNum; i++)
	{
		vertices[i].pos.x = (r / wc.WindowWidth()) * cos((PI * 2 / divNum) * i) + fx;
		vertices[i].pos.y = (r / wc.WindowHeight()) * sin((PI * 2 / divNum) * i) + fy;
		vertices[i].pos.z = 0;
		vertices[i].uv.x = 0;
		vertices[i].uv.y = 0;
	}

	D3D11_MAPPED_SUBRESOURCE mappedsub = {};
	result = dev.Context()->Map(_colorBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, &color, sizeof(unsigned int));
	dev.Context()->Unmap(_colorBuf, 0);

	mappedsub = {};
	result = dev.Context()->Map(_vbCircle, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedsub);
	memcpy(mappedsub.pData, vertices, sizeof(Vertex2D) * divNum);
	dev.Context()->Unmap(_vbCircle, 0);

	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	//DrawingStructure ds = {};
	//ds.vs = _vs2d;
	//ds.ps = _ps;
	//ds.layout = _layout;
	//ds.texture = nullptr;
	//ds.vb = vb;
	//ds.offset = 0;
	//ds.drawNum = divNum;
	//ds.colorBuffer = colorBuf;
	//ds.stride = sizeof(Vertex2D);

	if (fillFlag)
	{
		dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	}
	else
	{
		dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		//ds.topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	}

	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->IASetVertexBuffers(0, 1, &_vbCircle, &stride, &offset);

	dev.Context()->Draw(divNum, 0);
}
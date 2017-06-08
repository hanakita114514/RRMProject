#include "Graphic.h"
#include <D3DX11.h>
#include <D3D11.h>
#include <d3dx9tex.h>
#include "DeviceDx11.h"
#include "WindowControl.h"

Graphic::Graphic()
{
	HRESULT result = 
		Graphic::CreateShader(_vs2d, _vs3d, _layout, _ps);
}


Graphic::~Graphic()
{
}

ID3D11Buffer* 
Graphic::CreateBuffer2D(float x, float y, float width, float height)
{
	static int z = 0;

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

	return vb;
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
	bufdesc.Usage = D3D11_USAGE_DEFAULT;
	bufdesc.CPUAccessFlags = 0;
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
Graphic::LoadGraph(std::string filePath)
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

	if (result != S_OK)
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

HRESULT 
Graphic::LoadDivGraph(std::string filePath)
{
	HRESULT result = S_OK;

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

	if (result != S_OK)
	{
		handle = -1;
	}

	TexData data;
	D3DXIMAGE_INFO imageData;

	D3DXGetImageInfoFromFile(filePath.c_str(), &imageData);
	data.height = (float)imageData.Height;
	data.width = (float)imageData.Width;
	_texData[handle] = data;

	return result;
}

void 
Graphic::DrawGraph(float x, float y, int handle)
{
	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)handle;
	TexData t = _texData[handle];
	WindowControl& wc = WindowControl::Instance();
	//ID3D11Buffer* vBuffer = CreateBuffer2D(x, y, t.width, t.height);
	ID3D11Buffer* vBuffer = CreateBuffer2D(x + t.width / 2, y + t.height / 2, t.width, t.height);

	DeviceDx11& dev = DeviceDx11::Instance();
	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->PSSetShaderResources(0, 1, &texture);
	dev.Context()->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);

	dev.Context()->Draw(4, 0);
}

// 画像の分割描画
void 
Graphic::DrawRectGraph(float destX, float destY, int srcX, int srcY,
	int width, int height, int graphHandle, bool transFlag, bool trunFlag)
{
	HRESULT result;
	DeviceDx11& dev = DeviceDx11::Instance();
	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)graphHandle;
	TexData t = _texData[graphHandle];

	//バッファの生成
	//ID3D11Buffer* vBuffer = CreateBuffer2D(0, 0, 0, t.width, t.height);

	ID3D11Buffer* vb;

	Vertex2D vertices[4];

	int turn = 1;
	if (trunFlag)
	{
		turn = -1;
	}
	WindowControl& wc = WindowControl::Instance();

	//ウィンドウ座標系を-1～1にクランプ
	float x = destX + width / 2;
	float y = destY + height / 2;
	float fx = (x - wc.WindowWidth() / 2) / (wc.WindowWidth() / 2);
	float fy = ((y - wc.WindowHeight() / 2) / (wc.WindowHeight() / 2)) * -1;

	float fw = ((float)width / 2) / ((float)wc.WindowWidth() / 2);
	float fh = ((float)height / 2) / ((float)wc.WindowHeight() / 2);


	//左上
	vertices[0].pos.x = (fx - fw) * turn;
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = srcX / t.width;
	vertices[0].uv.y = srcY / t.height;

	//右上
	vertices[1].pos.x = (fx + fw) * turn;
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = (width + srcX) / t.width;
	vertices[1].uv.y = srcY / t.height;

	//左下
	vertices[2].pos.x = (fx - fw) * turn;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = srcX / t.width;;
	vertices[2].uv.y = (height + srcY) / t.height;

	//右下
	vertices[3].pos.x = (fx + fw) * turn;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = (width + srcX) / t.width;
	vertices[3].uv.y = (height + srcY) / t.height;


	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices[0]) * 4;
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DEFAULT;
	bufdesc.CPUAccessFlags = 0;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Vertex2D);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->PSSetShaderResources(0, 1, &texture);
	dev.Context()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

	dev.Context()->Draw(4, 0);
}

void 
Graphic::DrawExtendGraph(float lx, float ly, float rx, float ry, int handle)
{
	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)handle;
	TexData t = _texData[handle];
	WindowControl& wc = WindowControl::Instance();
	//ID3D11Buffer* vBuffer = CreateBuffer2D(x, y, t.width, t.height);

	float width = rx - lx;
	float height = ry - ly;


	ID3D11Buffer* vBuffer = CreateBuffer2D(lx + width / 2, ly + height / 2, width, height);

	DeviceDx11& dev = DeviceDx11::Instance();
	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->PSSetShaderResources(0, 1, &texture);
	dev.Context()->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);

	dev.Context()->Draw(4, 0);
}

void 
Graphic::DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY, int srcX, int srcY,
	int width, int height, int graphHandle, bool transFlag, bool trunFlag)
{
	HRESULT result;
	DeviceDx11& dev = DeviceDx11::Instance();
	ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*)graphHandle;
	TexData t = _texData[graphHandle];

	//バッファの生成
	//ID3D11Buffer* vBuffer = CreateBuffer2D(0, 0, 0, t.width, t.height);

	ID3D11Buffer* vb;

	Vertex2D vertices[4];

	int turn = 1;
	if (trunFlag)
	{
		turn = -1;
	}
	WindowControl& wc = WindowControl::Instance();

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
	vertices[0].pos.x = (fx - fw) * turn;
	vertices[0].pos.y = fy + fh;
	vertices[0].pos.z = 0;
	vertices[0].uv.x = srcX / t.width;
	vertices[0].uv.y = srcY / t.height;

	//右上
	vertices[1].pos.x = (fx + fw) * turn;
	vertices[1].pos.y = fy + fh;
	vertices[1].pos.z = 0;
	vertices[1].uv.x = (width + srcX) / t.width;
	vertices[1].uv.y = srcY / t.height;

	//左下
	vertices[2].pos.x = (fx - fw) * turn;
	vertices[2].pos.y = fy - fh;
	vertices[2].pos.z = 0;
	vertices[2].uv.x = srcX / t.width;;
	vertices[2].uv.y = (height + srcY) / t.height;

	//右下
	vertices[3].pos.x = (fx + fw) * turn;
	vertices[3].pos.y = fy - fh;
	vertices[3].pos.z = 0;
	vertices[3].uv.x = (width + srcX) / t.width;
	vertices[3].uv.y = (height + srcY) / t.height;

	//頂点バッファの作成
	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = sizeof(vertices[0]) * 4;
	bufdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufdesc.Usage = D3D11_USAGE_DEFAULT;
	bufdesc.CPUAccessFlags = 0;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = sizeof(Vertex2D);

	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = &vertices[0];

	result = dev.Device()->CreateBuffer(&bufdesc, &subdata, &vb);

	unsigned int offset = 0;
	unsigned int stride = sizeof(Vertex2D);

	dev.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dev.Context()->VSSetShader(_vs2d, nullptr, 0);
	dev.Context()->PSSetShader(_ps, nullptr, 0);
	dev.Context()->IASetInputLayout(_layout);
	dev.Context()->PSSetShaderResources(0, 1, &texture);
	dev.Context()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

	dev.Context()->Draw(4, 0);
}
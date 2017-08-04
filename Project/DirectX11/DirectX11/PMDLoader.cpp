#include "PMDLoader.h"
#include "PMDMesh.h"
#include "DeviceDx11.h"
#include "File.h"
#include <cassert>

using namespace RRMLib;

PMDLoader::PMDLoader()
{
	DeviceDx11& dev = DeviceDx11::Instance();
	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFile(
		dev.Device(),
		"nulltex.bmp",
		nullptr,
		nullptr,
		&_nulltex,
		nullptr);


	if (FAILED(hr))
	{
		assert("PMDLoader Error" && false);
	}

	hr = D3DX11CreateShaderResourceViewFromFile(
		dev.Device(),
		"nulltextureb.png",
		nullptr,
		nullptr,
		&_nulltexb,
		nullptr);

	if (FAILED(hr))
	{
		assert("PMDLoader Error" && false);
	}
}


PMDLoader::~PMDLoader()
{
}

PMDMesh* 
PMDLoader::LoadPMDFile(const std::string& filePath)
{
	DeviceDx11& dev = DeviceDx11::Instance();
	HRESULT hr = S_OK;

	File file(filePath.c_str(), "rb");

	//ファイル読み込み失敗
	if (file.IsFailed())
	{
		return nullptr;
	}

	PMDMesh* mesh = new PMDMesh();

	struct PMDHeader
	{
		float version;		//バージョン
		char name[20];		//名前
		char comment[256];	//コメント
		unsigned int vertexCont;	//頂点数
	};
	char sign[3];		//シグネチャー"pmd"

	//シグネチャ読み込み
	file.FileRead(&sign, sizeof(char) * 3, 1);

	PMDHeader header = {};

	file.FileRead(&header, sizeof(PMDHeader), 1);

	const int vert_size = 38;	//頂点データ(38バイト)

	std::vector<char> vertices(vert_size * header.vertexCont);
	file.FileRead(&vertices[0], vertices.size(), 1);

	//インデックスのロード
	//インデックス数
	unsigned int index_num;
	file.FileRead(&index_num, sizeof(index_num), 1);

	std::vector<unsigned short> indices(index_num);
	file.FileRead(&indices[0], indices.size() * sizeof(indices[0]), 1);

	//マテリアルのロード
	unsigned int material_num = 0;
	file.FileRead(&material_num, sizeof(unsigned int), 1);

	struct PMDMaterial
	{
		RGBColor diffuese_color;	//dr, dg, db 減衰色
		float alpha;				//減衰色の不透明度
		float specularity;			
		RGBColor specular_color;	//sr, sg, sb 光沢色
		RGBColor ambient;			//mr, mg, mb 環境色
		BYTE toon_index;			//toon?? bmp 0.bmp: 0xFF, 1(01)bmp:0x00 _ 10.mp:0x09
		BYTE edge_flag;				//輪郭、影
		DWORD face_vert_count;		//面頂点数
		char texture_file_name[20];	//テクスチャファイル名またはスフィアファイル名
	};



	return nullptr;
}

PMDMesh* 
PMDLoader::Load(const std::string& filePath)
{
	if (_pmdMap.find(filePath) == _pmdMap.end())
	{
		_pmdMap[filePath] = LoadPMDFile(filePath);
	}

	return _pmdMap[filePath];
}
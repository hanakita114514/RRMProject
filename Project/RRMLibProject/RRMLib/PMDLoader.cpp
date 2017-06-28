#include "PMDLoader.h"
#include "PMDMesh.h"
#include "DeviceDx11.h"
#include "File.h"
#include <cassert>


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
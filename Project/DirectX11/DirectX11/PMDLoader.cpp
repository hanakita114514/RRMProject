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

	//�t�@�C���ǂݍ��ݎ��s
	if (file.IsFailed())
	{
		return nullptr;
	}

	PMDMesh* mesh = new PMDMesh();

	struct PMDHeader
	{
		float version;		//�o�[�W����
		char name[20];		//���O
		char comment[256];	//�R�����g
		unsigned int vertexCont;	//���_��
	};
	char sign[3];		//�V�O�l�`���["pmd"

	//�V�O�l�`���ǂݍ���
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
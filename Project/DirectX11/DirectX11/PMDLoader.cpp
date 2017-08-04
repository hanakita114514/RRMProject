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

	const int vert_size = 38;	//���_�f�[�^(38�o�C�g)

	std::vector<char> vertices(vert_size * header.vertexCont);
	file.FileRead(&vertices[0], vertices.size(), 1);

	//�C���f�b�N�X�̃��[�h
	//�C���f�b�N�X��
	unsigned int index_num;
	file.FileRead(&index_num, sizeof(index_num), 1);

	std::vector<unsigned short> indices(index_num);
	file.FileRead(&indices[0], indices.size() * sizeof(indices[0]), 1);

	//�}�e���A���̃��[�h
	unsigned int material_num = 0;
	file.FileRead(&material_num, sizeof(unsigned int), 1);

	struct PMDMaterial
	{
		RGBColor diffuese_color;	//dr, dg, db �����F
		float alpha;				//�����F�̕s�����x
		float specularity;			
		RGBColor specular_color;	//sr, sg, sb ����F
		RGBColor ambient;			//mr, mg, mb ���F
		BYTE toon_index;			//toon?? bmp 0.bmp: 0xFF, 1(01)bmp:0x00 _ 10.mp:0x09
		BYTE edge_flag;				//�֊s�A�e
		DWORD face_vert_count;		//�ʒ��_��
		char texture_file_name[20];	//�e�N�X�`���t�@�C�����܂��̓X�t�B�A�t�@�C����
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
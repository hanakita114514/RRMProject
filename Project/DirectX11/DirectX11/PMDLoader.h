#pragma once

#include <string>
#include <map>

class PMDMesh;
class ID3D11ShaderResourceView;

class PMDLoader
{
private:

	std::map <std::string, PMDMesh*> _pmdMap;		//ロードしたPMDを格納する
	std::map<std::string, ID3D11ShaderResourceView*> _texMap;	//テクスチャマップ

	PMDMesh* LoadPMDFile(const std::string& filePath);

	ID3D11ShaderResourceView* _nulltex;
	ID3D11ShaderResourceView* _nulltexb;

public:
	PMDLoader();
	~PMDLoader();

	PMDMesh* Load(const std::string& filePath);
};


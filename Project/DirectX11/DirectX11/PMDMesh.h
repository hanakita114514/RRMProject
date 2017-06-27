#pragma once

#include <vector>
#include <string>
#include <map>
#include <D3DX11.h>
#include <xnamath.h>

struct ID3D11Buffer;
struct ID3D11ShaderResourceView;

class PMDLoader;

struct RGBColor
{
	float r, g, b;
};

class PMDMesh
{
public:
	struct Material
	{
		RGBColor diffuse;			//基本の色
		float alpha;
		float specularity;
		RGBColor specular;
		RGBColor ambient;			//
		unsigned int indexCount;	//インデックス数
		unsigned int indexOffset;	//オフセット
		ID3D11ShaderResourceView* texture;
		ID3D11ShaderResourceView* sph;
		ID3D11ShaderResourceView* spa;
	};

	//ボーン情報
	struct Bone
	{
		std::string name;	//ボーンの名前
		XMFLOAT3 headPos;	//起点
		XMFLOAT3 tailPos;	//終点
	};

	struct BoneNode
	{
		std::vector<int> children;
	};

	struct IKList
	{
		unsigned short boneIdx;			//IKボーンインデックス
		unsigned short tboneIds;		//ターゲットボーンインデックス(向きを確定)
		unsigned char ikchainLen;		//さかのぼりボーン数
		unsigned short iterationNu;		//巡回回数
		float restriction;				//制限角度
		std::vector<unsigned short> ikboneIndices;		//さかのぼりボーン番号
	};

private:

public:
	PMDMesh();
	~PMDMesh();
};


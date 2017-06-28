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
		RGBColor diffuse;			//��{�̐F
		float alpha;
		float specularity;
		RGBColor specular;
		RGBColor ambient;			//
		unsigned int indexCount;	//�C���f�b�N�X��
		unsigned int indexOffset;	//�I�t�Z�b�g
		ID3D11ShaderResourceView* texture;
		ID3D11ShaderResourceView* sph;
		ID3D11ShaderResourceView* spa;
	};

	//�{�[�����
	struct Bone
	{
		std::string name;	//�{�[���̖��O
		XMFLOAT3 headPos;	//�N�_
		XMFLOAT3 tailPos;	//�I�_
	};

	struct BoneNode
	{
		std::vector<int> children;
	};

	struct IKList
	{
		unsigned short boneIdx;			//IK�{�[���C���f�b�N�X
		unsigned short tboneIds;		//�^�[�Q�b�g�{�[���C���f�b�N�X(�������m��)
		unsigned char ikchainLen;		//�����̂ڂ�{�[����
		unsigned short iterationNu;		//�����
		float restriction;				//�����p�x
		std::vector<unsigned short> ikboneIndices;		//�����̂ڂ�{�[���ԍ�
	};

private:

public:
	PMDMesh();
	~PMDMesh();
};


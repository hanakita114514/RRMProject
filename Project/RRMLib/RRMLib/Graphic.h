#pragma once

#include <string>
#include "Vertex.h"
#include <map>


struct ID3D11ShaderResourceView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Buffer;

//�摜�̓ǂݍ��݁A�`����s��
class Graphic
{
private:
	struct TexData
	{
		float height;
		float width;
	};
private:
	ID3D11VertexShader* _vs2d;		//���_�V�F�[�_
	ID3D11VertexShader* _vs3d;		//���_�V�F�[�_
	ID3D11PixelShader* _ps;			//�s�N�Z���V�F�[�_
	ID3D11InputLayout* _layout;		//���C�A�E�g

	std::map<int, TexData> _texData;

	Graphic();
	Graphic(const Graphic&);
	Graphic& operator=(const Graphic&);

	ID3D11Buffer* CreateBuffer2D(float x, float y, float width, float height);
	ID3D11Buffer* CreateBuffer3D(float x, float y, float z, float width, float height);

	HRESULT CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps);

public:
	~Graphic();
	static Graphic& Instance()
	{
		static Graphic instance;

		return instance;
	}

	//�摜��ǂݍ���
	//�߂�l ���s�@-1 ���� ����ȊO�̐��l
	int LoadGraph(std::string filePath);

	//�摜�̕����ǂݍ���
	HRESULT LoadDivGraph(std::string filePath);

	//�摜�̕`��
	//���_���ォ��`��
	void DrawGraph(float x, float y, int handle);

	//�摜�̊g�k�`��
	// lx ly ������W
	// rx ry �E�����W
	// handle �摜�n���h��
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle);

	// �摜�̕����`��
	void DrawRectGraph(float destX, float destY,int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag);
};


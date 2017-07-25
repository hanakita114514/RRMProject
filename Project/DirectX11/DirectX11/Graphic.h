#pragma once

#include <string>
#include "Vertex.h"
#include <map>
#include "RRMCommon.h"

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
	ID3D11Buffer* _vb;				//���_�o�b�t�@

	std::map<int, TexData> _texData;


	//���_�o�b�t�@�̐���
	ID3D11Buffer* CreateBuffer2D(float x, float y, float width, float height);

	ID3D11Buffer* CreateBuffer2D(float x, float y, float width, float height, float luvX, float luvY, float ruvX, float ruvY,
		DrawingStructure& ds);
	//CPU���瓮�I����������
	ID3D11Buffer* CreateBuffer2DWrite(float x, float y, float width, float height, DrawingStructure& ds);

	void CreateVertex2D(float x, float y, float width, float height, Vertex2D* vertices, DrawingStructure& ds);

	ID3D11Buffer* CreateBuffer3D(float x, float y, float z, float width, float height);

	HRESULT CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps);

	//�V�F�[�_�p�ɍ��W���N�����v
	void CrampForShader(float& x, float& y);

public:
	Graphic();
	~Graphic();

	//���������ɌĂ�
	bool Init();
	void Terminate();

	//�摜��ǂݍ���
	//�߂�l ���s�@-1 ���� ����ȊO�̐��l
	int LoadTexture(std::string filePath);

	//�|���S���𐶐�
	DrawingStructure CreatePolygon();
	//�e�N�X�`���t���|���S���̐���
	int LoadGraph(std::string filePath);

	//�摜�̕����ǂݍ���
	HRESULT LoadDivGraph(std::string filePath, int allNum,
		int xNum, int yNum, int width, int height, int* handleBuf);

	//�摜�̕`��
	//���_���ォ��`��
	//void DrawGraph(float x, float y, int handle);
	//���ɐ������ꂽ�|���S�����g���č��W����`��
	void DrawGraph(float x, float y, int handle, bool transFlag);

	//�摜�̊g�k�`��
	// lx ly ������W
	// rx ry �E�����W
	// handle �摜�n���h��
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle, bool transFlag, bool turnFlag);

	// �摜�̕����`��
	void DrawRectGraph(float destX, float destY,int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool turnFlag);

	//�摜�̕����g�k�`��
	void DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool turnFlag);

	//�摜�̉�]�`��
	void DrawRotaGraphProt(float x, float y, double angle, int graphHandle, bool transFlag, bool turnFlag);

	void DrawRotaGraph(float x, float y, double angle, int graphHandle, bool transFlag, bool turnFlag);


	//�摜�̍폜
	void DeleteGraph(int handle);
};


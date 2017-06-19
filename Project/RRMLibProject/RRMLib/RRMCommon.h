#pragma once
#include "Vertex.h"

struct ID3D11ShaderResourceView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Buffer;

struct VBufferData2D
{
	XMFLOAT2 luv;		//����UV
	XMFLOAT2 ruv;		//�E��UV
	float width;		//�摜�̕�
	float height;		//�摜�̍���
};

struct DrawingStructure
{
	ID3D11VertexShader* vs;				//���_�V�F�[�_
	ID3D11PixelShader* ps;				//�s�N�Z���V�F�[�_
	ID3D11InputLayout* layout;			//���C�A�E�g
	ID3D11Buffer* colorBuffer;			//�R���X�^���g�o�b�t�@
	ID3D11ShaderResourceView* texture;	//�e�N�X�`��
	VBufferData2D vertex;				//���_�f�[�^
	int texSlot;						//�e�N�X�`���̃��W�X�^�ԍ�
	int topology;						//�v���~�e�B�u�g�|���W�[
	unsigned int offset;				//�I�t�Z�b�g
	unsigned int stride;				//�X�g���C�h
	unsigned int drawNum;				//���_��
};
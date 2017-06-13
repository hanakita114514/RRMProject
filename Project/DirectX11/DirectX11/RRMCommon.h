#pragma once

struct ID3D11ShaderResourceView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Buffer;

struct DrawingStructure
{
	ID3D11VertexShader* vs;				//���_�V�F�[�_
	ID3D11PixelShader* ps;				//�s�N�Z���V�F�[�_
	ID3D11InputLayout* layout;			//���C�A�E�g
	ID3D11Buffer* vb;					//���_�o�b�t�@
	ID3D11Buffer* colorBuffer;			//�R���X�^���g�o�b�t�@
	ID3D11ShaderResourceView* texture;	//�e�N�X�`��
	int texSlot;						//�e�N�X�`���̃��W�X�^�ԍ�
	int topology;	//�v���~�e�B�u�g�|���W�[
	unsigned int offset;				//�I�t�Z�b�g
	unsigned int stride;				//�X�g���C�h
	unsigned int drawNum;				//���_��
};
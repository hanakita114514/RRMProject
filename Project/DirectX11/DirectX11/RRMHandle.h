#pragma once

struct HandleList
{
	int handle;
	void *data;
	HandleList* prev;
	HandleList* next;
};

struct HandleInfo
{
	int id;				//�G���[�`�F�b�N
	int handle;			//�f�[�^�n���h��
	bool deleteFlag;	//�폜���ꂽ��true
	int asyncLoadResult;//�񓯊��ǂݍ��݂̌���
	HandleList list;	//���ƑO�̃|�C���^

	HandleInfo() : id(0), handle(-1), deleteFlag(false),
		asyncLoadResult(true)
	{

	}
};

void HandleInit(HandleInfo& handleInfo);
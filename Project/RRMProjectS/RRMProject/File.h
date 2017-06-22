#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include "MapRendar.h"
#include "GameMain.h"

class RectObj;

enum class FILE_INIT_TYPE			//�t�@�C�����J���Ƃ��̃��[�h�i����̓o�C�i���̂݁j
{
	FILE_READ,				//�ǂݍ���
	FILE_WRITE				//��������
};

class File
{
private:
	errno_t _err;			//�G���[�`�F�b�N�ϐ�
	const char* _fileName;		//�t�@�C����
	FILE* _filePointer;		//�|�C���^�[

public:
	File(const char* filePath);	
	~File();

	bool Initialize();
	bool Initialize(FILE_INIT_TYPE type);	//�t�@�C���̃��[�h���w�肷��

	void Finalize();

	void FileLoad(FMFHEADER& header, vector<vector<int>>& array);

	//�S�f�[�^�ǂݍ���
	void FileLoad(SaveData& data, int size);

	//�S�f�[�^��������
	void FileWrite(const SaveData& data);
};
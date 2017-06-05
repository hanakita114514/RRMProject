#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include "MapRendar.h"

enum class FILE_INIT_TYPE			//�t�@�C�����J���Ƃ��̃��[�h�i����̓o�C�i���̂݁j
{
	FILE_READ,				//�ǂݍ���
	FILE_WRITE				//��������
};

class MyFile
{
private:
	errno_t _err;			//�G���[�`�F�b�N�ϐ�
	char* _fileName;		//�t�@�C����
	FILE* _filePointer;		//�|�C���^�[

public:
	MyFile(char* filePath);	
	~MyFile();

	bool Initialize();
	bool Initialize(FILE_INIT_TYPE type);	//�t�@�C���̃��[�h���w�肷��

	void Finalize();

	void FileLoad(FMFHEADER& header, vector<vector<vector<unsigned int>>>& array);
};
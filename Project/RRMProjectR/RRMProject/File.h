#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include <typeinfo>
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

	bool FileRead(void* buffer, int size, int num,int seek = 0);
	bool FileWrite(void* buffer, int size, int num);

	void Finalize();

};
#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include "MapRendar.h"
#include "GameMain.h"

class RectObj;

enum class FILE_INIT_TYPE			//ファイルを開くときのモード（現状はバイナリのみ）
{
	FILE_READ,				//読み込み
	FILE_WRITE				//書き込み
};

class File
{
private:
	errno_t _err;			//エラーチェック変数
	const char* _fileName;		//ファイル名
	FILE* _filePointer;		//ポインター

public:
	File(const char* filePath);	
	~File();

	bool Initialize();
	bool Initialize(FILE_INIT_TYPE type);	//ファイルのモードを指定する

	void Finalize();

	void FileLoad(FMFHEADER& header, vector<vector<int>>& array);

	//全データ読み込み
	void FileLoad(SaveData& data, int size);

	//全データ書き込み
	void FileWrite(const SaveData& data);
};
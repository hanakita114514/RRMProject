#include "MyFile.h"
#define BYTE1(x)   (x & 0xff)
#define BYTE2(x)	((x >> 8) & 0xff)
#define BYTE3(x)	((x >> 16) & 0xff)
#define BYTE4(x)	((x >> 24) & 0xff)

#define BYTE_SWAP(x)		(BYTE1(x))
#define BYTE_SWAP_16(x)		((uint16_t)(BYTE1(x) << 8 | BYTE2(x)))
#define BYTE_SWAP_32(x)		((uint32_t)(BYTE1(x) << 24 | BYTE2(x) << 16 | BYTE3(x) << 8 | BYTE4(x)))

using namespace std;
MyFile::MyFile(char* filePath)
{
	_fileName = filePath;
}


MyFile::~MyFile()
{

}

bool MyFile::Initialize()
{
	_err = fopen_s(&_filePointer, _fileName, "rb");

	if (_err != 0)			//オープンに失敗したか？
	{
		return false;
	}

	return true;
}
bool MyFile::Initialize(FILE_INIT_TYPE type)
{
	switch (type)
	{
	case FILE_INIT_TYPE::FILE_READ:				//読み込み
	{
		_err = fopen_s(&_filePointer, _fileName, "rb");
		if (_err != 0)			//オープンに失敗したか？
		{
			return false;
		}
	}
		break;
	case FILE_INIT_TYPE::FILE_WRITE:			//書き込み
	{
		fopen_s(&_filePointer, _fileName, "wb");
	}
		break;
	default:
		break;
	}

	return true;
}

void MyFile::Finalize()
{
	fclose(_filePointer);
}

void MyFile::FileLoad(FMFHEADER& header, vector<vector<vector<unsigned int>>>& array)
{
	int i, y, x;		//ループ用変数

	fseek(_filePointer, 0, SEEK_SET);

	fread(&header, sizeof(header), 1, _filePointer);	//ヘッダ情報を書き込む

	int layerSize = header.byLayerCount;				//レイヤーの数
	int height = header.dwHeight;						//マップの高さ
	int width = header.dwWidth;							//マップの幅

	array.resize(layerSize);

	for (i = 0; i < layerSize; ++i)
	{
		array[i].resize(height);
		for (y = 0; y < height; ++y)
		{
			array[i][y].resize(width);
		}
	}

	//マップ読み込みループ-----------------------------------------------------------------
	for (i = 0; i < layerSize; ++i)
	{
		for (y = 0; y < height; ++y)
		{
			for (x = 0; x < width; ++x)
			{
				//マップ情報を読み込む
				fread(&array[i][y][x], sizeof(unsigned char), 1, _filePointer);
			}
		}
	}
	//--------------------------------------------------------------------------------------
}


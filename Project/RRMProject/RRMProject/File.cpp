#include "File.h"
#define BYTE1(x)   (x & 0xff)
#define BYTE2(x)	((x >> 8) & 0xff)
#define BYTE3(x)	((x >> 16) & 0xff)
#define BYTE4(x)	((x >> 24) & 0xff)

#define BYTE_SWAP(x)		(BYTE1(x))
#define BYTE_SWAP_16(x)		((uint16_t)(BYTE1(x) << 8 | BYTE2(x)))
#define BYTE_SWAP_32(x)		((uint32_t)(BYTE1(x) << 24 | BYTE2(x) << 16 | BYTE3(x) << 8 | BYTE4(x)))

using namespace std;
File::File(const char* filePath)
{
	_fileName = filePath;
}


File::~File()
{

}

bool File::Initialize()
{
	_err = fopen_s(&_filePointer, _fileName, "rb");

	if (_err != 0)			//オープンに失敗したか？
	{
		return false;
	}

	return true;
}
bool File::Initialize(FILE_INIT_TYPE type)
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

void File::Finalize()
{
	fclose(_filePointer);
}

void File::FileLoad(FMFHEADER& header, vector<vector<unsigned int>>& array)
{
	int i, y, x;		//ループ用変数

	fseek(_filePointer, 0, SEEK_SET);

	fread(&header, sizeof(header), 1, _filePointer);	//ヘッダ情報を書き込む

	int layerSize = header.byLayerCount;				//レイヤーの数
	int height = header.dwHeight;						//マップの高さ
	int width = header.dwWidth;							//マップの幅

	array.resize(header.dwHeight);

	for (i = 0; i < header.dwHeight; ++i)
	{
		array[i].resize(header.dwWidth);
	}

	//マップ読み込みループ-----------------------------------------------------------------		
	for (y = 0; y < height; ++y)
		{
			for (x = 0; x < width; ++x)
			{
				//マップ情報を読み込む
				fread(&array[y][x], sizeof(unsigned char), 1, _filePointer);
			}
		}
	
	i = 0;
	//--------------------------------------------------------------------------------------
}


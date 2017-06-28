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
	Finalize();
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

//エラーならばfalse,成功ならtrueを返す
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

bool
File::FileRead(void* buffer, int size, int num,int seek)
{
	int err;
	fseek(_filePointer, seek, SEEK_SET);

	err = fread(buffer, size, num, _filePointer);
	if (err < num)
	{
		return false;
	}
	return true;
}

bool
File::FileWrite(void* buffer, int size, int num)
{
	fseek(_filePointer, 0, SEEK_SET);

	int err;
	err = fwrite(buffer, size, num, _filePointer);

	if (err < num)
	{
		return false;
	}
	return true;
}

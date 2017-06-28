#pragma once

struct _iobuf;
typedef _iobuf FILE;

namespace RRMLib
{
	class File
	{
	private:
		FILE* _fp;

		bool _isFailed;		//ファイル読み込み失敗したか？

	public:
		File(const char* filePath, const char* mode);
		~File();

		bool IsFailed() { return _isFailed; }

		void FileRead(void* buffer, int size, int num);
		void FileSeek();
	};
}

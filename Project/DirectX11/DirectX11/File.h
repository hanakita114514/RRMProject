#pragma once

struct _iobuf;
typedef _iobuf FILE;

namespace RRMLib
{
	class File
	{
	private:
		FILE* _fp;

		bool _isFailed;		//�t�@�C���ǂݍ��ݎ��s�������H

	public:
		File(const char* filePath, const char* mode);
		~File();

		bool IsFailed() { return _isFailed; }

		void FileRead(void* buffer, int size, int num);
		void FileSeek();
	};
}

#include "File.h"
#include <stdio.h>
#include <cassert>

File::File(const char* filePath, const char* mode)
{
	_fp = fopen(filePath, mode);
	_isFailed = false;

	if (_fp == nullptr)
	{
		//MessageBox(nullptr, "file not found", "Error", MB_OK);
		assert("file not found" && false);
		_isFailed = true;
	}
}


File::~File()
{
	fclose(_fp);
}


void 
File::FileRead(void* buffer, int size, int num)
{
	fread(buffer, size, num, _fp);
}

void 
File::FileSeek()
{
}
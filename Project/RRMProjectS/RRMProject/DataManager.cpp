#include "DataManager.h"
#include "File.h"
char* _filePath[(int)FileType::max] = 
{ 
	{ "Resource/data/save/sys.dat" },
	{"Resource/data/save/character/dat"}
};

DataManager::DataManager()
{

}


DataManager::~DataManager()
{
}

void
DataManager::Save(FileType type,SysData& data)
{
	File* file = new File(_filePath[(int)type]);
	_err = file->Initialize(FILE_INIT_TYPE::FILE_WRITE);

	if (!_err)				//ファイルオープンに失敗
	{
		data.firstStratUp = true;
		data.stageProgress = 0;
	}
	else
	{
		file->FileLoad(data, sizeof(SysData));
		file->FileWrite(data);
	}

}

void
DataManager::Load(FileType type , SysData& data)
{
	File* file = new File(_filePath[(int)type]);
	_err = file->Initialize(FILE_INIT_TYPE::FILE_READ);

	if (!_err)				//ファイルオープンに失敗
	{
		data.firstStratUp = true;
		data.stageProgress = 0;
	}
	else
	{
		file->FileLoad(data, sizeof(SysData));
	}
}

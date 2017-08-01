#include "DataManager.h"
#include "File.h"

DataManager::DataManager()
{

}


DataManager::~DataManager()
{
}

void
DataManager::Save(SaveData& data)
{
	File* file = new File("Resource/data/save/saveData.rrm");
	file->FileWrite(&data,sizeof(SaveData),1);
}

void
DataManager::Save(SysData& data)
{
	File* file = new File("Resource/data/save/system.rrm");
	file->FileWrite(&data, sizeof(SysData), 1);
}

void
DataManager::Load(SaveData& data)
{
	File* file = new File( "Resource/data/save/saveData.rrm");
	
	if (_err = file->FileRead(&data, sizeof(SaveData), 1) != true)
	{
		SaveData defaultData = {};
		data = defaultData;
		Save(data);
	}
}

void
DataManager::Load(SysData& data)
{
	File* file = new File("Resource/data/save/system.rrm");

	_err = file->FileRead(&data, sizeof(SaveData), 1);
	if(!_err)
	{
		SysData defaultData = {100,100};
		data = defaultData;
		Save(data);
	}
}

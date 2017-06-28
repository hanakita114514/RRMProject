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
	file->Initialize(FILE_INIT_TYPE::FILE_WRITE);
	file->FileWrite(&data,sizeof(SaveData),1);
}

void
DataManager::Load(SaveData& data)
{
	File* file = new File( "Resource/data/save/saveData.rrm");
	if (_err = file->Initialize(FILE_INIT_TYPE::FILE_READ))
	{
		file->FileRead(&data,sizeof(SaveData),1);
	}
	else
	{
		SaveData defaultData = {};
		data = defaultData;
		Save(data);
	}

}

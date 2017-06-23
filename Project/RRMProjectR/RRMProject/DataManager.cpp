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
	file->FileWrite(data);
}

void
DataManager::Load(SaveData& data)
{
	File* file = new File( "Resource/data/save/saveData.rrm");
	if (_err = file->Initialize(FILE_INIT_TYPE::FILE_READ))
	{
		file->FileLoad(data, sizeof(SaveData));
	}
	else
	{
		SaveData defaultData = {};
		data = defaultData;
		Save(data);
	}

}

#pragma once

class File;

typedef struct SYSTEM_DATA
{
	bool firstStratUp;		//初回起動か？
	int stageProgress;		//ステージの進行状況

}SysData;

enum class FileType
{
	system,
	character,

	max
};

class DataManager
{
private:
	bool _err;
public:
	DataManager();
	~DataManager();

	void Save(FileType type, SysData& data);

	void Load(FileType type, SysData& data);

};


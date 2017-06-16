#pragma once

class File;

typedef struct SYSTEM_DATA
{
	bool firstStratUp;		//����N�����H
	int stageProgress;		//�X�e�[�W�̐i�s��

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


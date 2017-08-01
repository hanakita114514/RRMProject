#pragma once

class File;



struct EquipmentInfometion
{
	unsigned int tool[3];				//���ݑ������Ă����ѓ���
	unsigned int weapon[2];				//���ݑ������Ă��镐��̏��
	int chooseToolNum;			
	int chooseWeaponNum;		
};

//�Z�[�u�f�[�^�\����
typedef struct SAVE_DATA
{
	int stageProgress;			//�X�e�[�W�̐i�s��
	EquipmentInfometion equipData;
}SaveData;

typedef struct SYSTEM_DATA
{
	int _bgmVolume;
	int _seVolume;
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
	DataManager();
public:

	static DataManager Instance()
	{
		static DataManager instance;
		return instance;
	}

	~DataManager();

	//���ׂẴf�[�^����������(��{�I�ɂ͂��������g��)
	void Save(SaveData& data);
	void Save(SysData& data);

	//���ׂẴf�[�^��ǂݍ���(��{�I�ɂ͂��������g��)
	void Load(SaveData& data);
	void Load(SysData& data);
};


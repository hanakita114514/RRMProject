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

	//���ׂẴf�[�^����������(��{�I�ɂ͂��������g��)
	void Save(SaveData& data);

	//���ׂẴf�[�^��ǂݍ���(��{�I�ɂ͂��������g��)
	void Load(SaveData& data);

};


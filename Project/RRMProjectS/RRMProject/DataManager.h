#pragma once

class File;

//�Z�[�u�f�[�^�\����
typedef struct SAVE_DATA
{
	int stageProgress;			//�X�e�[�W�̐i�s��
	unsigned int  tool[3];		//���ݑ������Ă����ѓ���
	unsigned int weapon[2];		//���ݑ������Ă���ߐڕ���
	int chooseToolNum;			//�I�����邱�Ƃ��ł����ѓ���̐�
	int chooseWeaponNum;		//�I�����邱�Ƃ��ł��镐��̐�
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


#pragma once

class File;



struct EquipmentInfometion
{
	unsigned int tool[3];				//現在装備している飛び道具
	unsigned int weapon[2];				//現在装備している武器の情報
	int chooseToolNum;			
	int chooseWeaponNum;		
};

//セーブデータ構造体
typedef struct SAVE_DATA
{
	int stageProgress;			//ステージの進行状況
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

	//すべてのデータを書き込む(基本的にはこっちを使う)
	void Save(SaveData& data);

	//すべてのデータを読み込む(基本的にはこっちを使う)
	void Load(SaveData& data);

};


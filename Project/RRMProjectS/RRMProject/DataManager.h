#pragma once

class File;

//セーブデータ構造体
typedef struct SAVE_DATA
{
	int stageProgress;			//ステージの進行状況
	unsigned int  tool[3];		//現在装備している飛び道具
	unsigned int weapon[2];		//現在装備している近接武器
	int chooseToolNum;			//選択することができる飛び道具の数
	int chooseWeaponNum;		//選択することができる武器の数
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


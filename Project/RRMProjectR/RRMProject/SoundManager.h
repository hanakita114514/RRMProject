#pragma once

#include <map>


enum class SoundType
{
	title,
	stage1,
	stage2,
	stage3,
	bossBattle,
};

enum class SEType
{
	firstAttack,			//攻撃そのいち
	secondAttack,			//攻撃そのに
	thirdAttack,			//攻撃そのさん
	damage,					//ダメージ
	player_dead,			//プレイヤー死亡
	decision,				//決定ボタン
	decision2,				//決定ボタン（その2） 某艦これのような音
	explosion,				//爆発
	jump,					//ジャンプ
	select,					//選択
	avoid,					//回避
	shot,					//飛び道具
};

class SoundManager
{
private:
	SoundManager();
	SoundManager(const SoundManager&);
	SoundManager& operator = (const SoundManager&);

	std::map<SoundType, int> _soundMap;
	std::map<SEType, int> _seMap;

public:
	~SoundManager();

	static SoundManager& Instance()
	{
		static SoundManager instance;

		return instance;
	}

	void Play(SoundType st);
	void Play(SEType se);

	void PlayFromStart(SoundType st);
	void PlayFromStart(SEType se);

	void BGMVolumeChange(int vol,SoundType type);
	void SEVolumeChange(int vol, SEType type);


	//全部の曲を止める
	void Stop();
};


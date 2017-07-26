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
	firstAttack,
	secondAttack,
	thirdAttack,
	damage,
	player_dead,
	decision,
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

	//‘S•”‚Ì‹È‚ðŽ~‚ß‚é
	void Stop();
};


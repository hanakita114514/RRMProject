#pragma once

#include <map>


enum class SoundType
{

};

enum class SEType
{

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

	//‘S•”‚Ì‹È‚ğ~‚ß‚é
	void Stop();
};


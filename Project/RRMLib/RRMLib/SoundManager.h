#pragma once

class SoundManager
{
private:
	SoundManager();
	SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager&);

public:
	~SoundManager();

	static SoundManager& Instance()
	{
		static SoundManager instance;

		return instance;
	}

	void Init();
	void Load();
	void Play(int cueId);
	void Terminate();
	void Update();

};


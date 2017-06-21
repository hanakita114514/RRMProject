#include "SoundManager.h"
#include <RRMLib.h>


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void
SoundManager::Play(SoundType st)
{
	RRMLib::PlaySoundMem(_soundMap[st]);
}

void
SoundManager::Play(SEType se)
{
	RRMLib::PlaySoundMem(_seMap[se]);
}

void
SoundManager::Stop()
{
	for (auto s : _soundMap)
	{
		RRMLib::StopSound(s.second);
	}
}
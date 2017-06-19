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
	//PlaySoundMem(_soundMap[st], DX_PLAYTYPE_BACK, true);
}

void
SoundManager::Play(SEType se)
{
	//PlaySoundMem(_seMap[se], DX_PLAYTYPE_BACK, true);

}

void
SoundManager::Stop()
{
	for (auto s : _soundMap)
	{
		//StopSoundMem(s.second);
	}
}
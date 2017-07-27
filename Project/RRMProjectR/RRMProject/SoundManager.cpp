#include "SoundManager.h"
#include <RRMLib.h>


SoundManager::SoundManager()
{
	_soundMap[SoundType::title] = RRMLib::LoadSound(L"Resource/sound/BGM/titleBGM.mp3");
	_soundMap[SoundType::stage1] = RRMLib::LoadSound(L"Resource/sound/BGM/Stage1BGM.mp3");
	_soundMap[SoundType::stage2] = RRMLib::LoadSound(L"Resource/sound/BGM/Stage2BGM.mp3");
	_soundMap[SoundType::stage3] = RRMLib::LoadSound(L"Resource/sound/BGM/Stage3BGM.mp3");
	_soundMap[SoundType::bossBattle] = RRMLib::LoadSound(L"Resource/sound/BGM/bossBattle.mp3");

	_seMap[SEType::firstAttack] = RRMLib::LoadSound(L"Resource/sound/SE/firstAttack.mp3");
	_seMap[SEType::secondAttack] = RRMLib::LoadSound(L"Resource/sound/SE/secondAttack.mp3");
	_seMap[SEType::thirdAttack] = RRMLib::LoadSound(L"Resource/sound/SE/thirdAttack.mp3");
	_seMap[SEType::player_dead] = RRMLib::LoadSound(L"Resource/sound/SE/Explosion.mp3");
	_seMap[SEType::damage] = RRMLib::LoadSound(L"Resource/sound/SE/Damage.mp3");
	_seMap[SEType::decision] = RRMLib::LoadSound(L"Resource/sound/SE/DecisionSE.mp3");
	_seMap[SEType::explosion] = RRMLib::LoadSound(L"Resource/sound/SE/Explosion.mp3");
	_seMap[SEType::jump] = RRMLib::LoadSound(L"Resource/sound/SE/jump.mp3");
	_seMap[SEType::select] = RRMLib::LoadSound(L"Resource/sound/SE/select.mp3");
	_seMap[SEType::avoid] = RRMLib::LoadSound(L"Resource/sound/SE/avoid.mp3");
	_seMap[SEType::shot] = RRMLib::LoadSound(L"Resource/sound/SE/shot.wav");
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
SoundManager::PlayFromStart(SoundType st)
{
	RRMLib::PlayFromStart(_soundMap[st]);
}

void
SoundManager::PlayFromStart(SEType se)
{
	RRMLib::PlayFromStart(_seMap[se]);
}

void
SoundManager::Stop()
{
	for (auto s : _soundMap)
	{
		RRMLib::StopSound(s.second);
	}
}
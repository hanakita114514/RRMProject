#include "MediaControl.h"



MediaControl::MediaControl()
{
}


MediaControl::~MediaControl()
{
}

int 
MediaControl::Load(BSTR filePath)
{
	int handle;
	_mediaMap[filePath] = new MediaPlayer(filePath);
	bool result = _mediaMap[filePath]->Init();
	if (!result)
	{
		return -1;
	}

	handle = (int)_mediaMap[filePath];

	return handle;
}

void 
MediaControl::Play(int handle)
{
	MediaPlayer* mp = (MediaPlayer*)handle;

	mp->Play();
}

void 
MediaControl::PlayFromStart(int handle)
{
	MediaPlayer* mp = (MediaPlayer*)handle;
	mp->PlayFromStart();
}

void 
MediaControl::Pause(int handle)
{
	MediaPlayer* mp = (MediaPlayer*)handle;
	mp->Pause();
}

void 
MediaControl::Stop(int handle)
{
	MediaPlayer* mp = (MediaPlayer*)handle;
	mp->Stop();
}

void 
MediaControl::SetVolume(long vol, int handle)
{
	MediaPlayer* mp = (MediaPlayer*)handle;
	mp->SetVolume(vol);
}

long 
MediaControl::GetVolume(int handle)
{
	MediaPlayer* mp = (MediaPlayer*)handle;
	long vol = mp->GetVolume();
	return vol;
}

void 
MediaControl::Terminate()
{
	for (auto m : _mediaMap)
	{
		if (m.second)
		{
			m.second->Terminate();
			delete m.second;
		}
	}
}
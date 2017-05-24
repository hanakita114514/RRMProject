#include "MediaPlayer.h"
#include <string>
#include <codecvt> 

const long MAX_VOLUME = 0;
const long MIN_VOLUME = -10000;

const long VOLUME_CLAMP = 10000;

MediaPlayer::MediaPlayer(BSTR filePath)
{
	_filePath = filePath;
}


MediaPlayer::~MediaPlayer()
{
}

bool
MediaPlayer::Init()
{
	HRESULT hr = S_OK;
	//COMを初期化
	//hr = CoInitialize(nullptr);
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (FAILED(hr))
	{
		return false;
	}
	//FilterGraphを生成
	hr = CoCreateInstance(CLSID_FilterGraph,
		nullptr,
		CLSCTX_INPROC,
		IID_IGraphBuilder,
		(LPVOID*)&pGraphBuilder);

	if (FAILED(hr))
	{
		return false;
	}
	//MediaControlインターフェイス
	hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
		(LPVOID*)&pMediaControl);

	if (FAILED(hr))
	{
		return false;
	}

	//再生位置のインターフェイス
	hr = pGraphBuilder->QueryInterface(IID_IMediaPosition, (LPVOID *)&pMediaPosition);

	if (FAILED(hr))
	{
		return false;
	}

	hr = pMediaControl->RenderFile(_filePath);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void 
MediaPlayer::Play()
{
	//Graphを生成
	pMediaControl->Run();
}

//再生中の場合でも先頭に戻して再生し直す
void 
MediaPlayer::PlayFromStart()
{
	pMediaPosition->put_CurrentPosition(0);
	pMediaControl->Run();

}

void 
MediaPlayer::Pause()
{
	pMediaControl->Pause();
}

void
MediaPlayer::Stop()
{
	pMediaControl->Stop();
	pMediaPosition->put_CurrentPosition(0);
}


void 
MediaPlayer::SetVolume(long vol)
{
	IBasicAudio *pBasicAudio;
	pGraphBuilder->QueryInterface(IID_IBasicAudio, (LPVOID *)&pBasicAudio);

	//音量の範囲を0～10000に設定するため
	vol -= VOLUME_CLAMP;
	if (vol > MAX_VOLUME)
	{
		vol = MAX_VOLUME;
	}
	else if (vol < MIN_VOLUME)
	{
		vol = MIN_VOLUME;
	}

	pBasicAudio->put_Volume(vol);

	pBasicAudio->Release();
}

long 
MediaPlayer::GetVolume()
{
	IBasicAudio *pBasicAudio;
	pGraphBuilder->QueryInterface(IID_IBasicAudio, (LPVOID *)&pBasicAudio);

	long volume = 0;

	pBasicAudio->get_Volume(&volume);

	pBasicAudio->Release();

	return volume + VOLUME_CLAMP;
}


void
MediaPlayer::Terminate()
{
	if (pMediaPosition) 
	{
		pMediaPosition->Release();
		pMediaPosition = nullptr;
	}

	if (pMediaControl) 
	{
		pMediaControl->Release();
		pMediaControl = nullptr;
	}

	if (pGraphBuilder) 
	{
		pGraphBuilder->Release();
		pGraphBuilder = nullptr;

		CoUninitialize();
	}
}
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
	//COM��������
	//hr = CoInitialize(nullptr);
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (FAILED(hr))
	{
		return false;
	}
	//FilterGraph�𐶐�
	hr = CoCreateInstance(CLSID_FilterGraph,
		nullptr,
		CLSCTX_INPROC,
		IID_IGraphBuilder,
		(LPVOID*)&pGraphBuilder);

	if (FAILED(hr))
	{
		return false;
	}
	//MediaControl�C���^�[�t�F�C�X
	hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
		(LPVOID*)&pMediaControl);

	if (FAILED(hr))
	{
		return false;
	}

	//�Đ��ʒu�̃C���^�[�t�F�C�X
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
	//Graph�𐶐�
	pMediaControl->Run();
}

//�Đ����̏ꍇ�ł��擪�ɖ߂��čĐ�������
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

	//���ʂ͈̔͂�0�`10000�ɐݒ肷�邽��
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
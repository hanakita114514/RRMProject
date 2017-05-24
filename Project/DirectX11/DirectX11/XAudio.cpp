#include "XAudio.h"
#include <XAudio2.h>
#include <stdio.h>

//XAudio2
IXAudio2* pXAudio2;
IXAudio2MasteringVoice* pMasterVoice = nullptr;
IXAudio2SourceVoice* pSourceVoice;

//テスト用

//std::vector<BYTE> data;

std::vector<unsigned short> audiodata;

XAudio::XAudio()
{
}


XAudio::~XAudio()
{
}

void
XAudio::Init()
{
	//XAudio2の初期化処理
	HRESULT hr;

	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		return;
	}


	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice, XAUDIO2_DEFAULT_CHANNELS,
		XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, nullptr)))
	{
		return;
	}

	////ソースボイスの作成
	//WAVEFORMATEX wavformat = {};

	//wavformat.wFormatTag = WAVE_FORMAT_PCM;
	//wavformat.nChannels = 1;
	//wavformat.wBitsPerSample = 16;
	//wavformat.nSamplesPerSec = 44100;
	//wavformat.nBlockAlign = wavformat.wBitsPerSample / 8 * wavformat.nChannels;
	//wavformat.nAvgBytesPerSec = wavformat.nSamplesPerSec * wavformat.nBlockAlign;

	//hr = pXAudio2->CreateSourceVoice(&pSourceVoice, &wavformat);

	////1秒分のバッファ
	//data.resize(wavformat.nAvgBytesPerSec * 1);
	//short* p = (short*)&data[0];
	//for (size_t i = 0; i < data.size() / 2; i++)
	//{
	//	float length = wavformat.nSamplesPerSec / 440.0f;
	//	*p = (short)(32767 * sinf(i * 3.1415926535f / (length / 2)));
	//	p++;
	//}

	////サウンドバッファの作成
	//XAUDIO2_BUFFER audiobuffer = {};
	//audiobuffer.Flags = XAUDIO2_END_OF_STREAM;
	//audiobuffer.AudioBytes = data.size();
	//audiobuffer.pAudioData = &data[0];

	//hr = pSourceVoice->SubmitSourceBuffer(&audiobuffer);
}

void
XAudio::Play()
{
	pSourceVoice->Start();
}

bool 
XAudio::MP3Read(const std::string& filePath)
{
	bool result = readMp3.Read(filePath);
	//bool result = readMp3.ReadTest(filePath);

	if (!result)
	{
		return false;
	}

	WavForMp3 wf = readMp3.GetWavFormat();

	//ソースボイスの作成
	WAVEFORMATEX wavformat = {};

	wavformat.wFormatTag = wf.wFormatTag;
	wavformat.nChannels = wf.nChannels;
	wavformat.wBitsPerSample = wf.wBitsPerSample;
	wavformat.nSamplesPerSec = wf.nSamplesPerSec;

	wavformat.nBlockAlign = wf.nBlockAlign;
	wavformat.nAvgBytesPerSec = wf.nAvgBytesPerSec;

	HRESULT hr = pXAudio2->CreateSourceVoice(&pSourceVoice, &wavformat);

	//サウンドバッファの作成
	XAUDIO2_BUFFER audiobuffer = {};
	audiobuffer.Flags = XAUDIO2_END_OF_STREAM;
	audiobuffer.AudioBytes = readMp3.GetBuffer().size();
	audiobuffer.pAudioData = (BYTE*)&readMp3.GetBuffer()[0];

	hr = pSourceVoice->SubmitSourceBuffer(&audiobuffer);

	return true;
}

bool 
XAudio::WavRead(const std::string& filePath)
{
	FILE* fp = fopen(filePath.c_str(), "rb");

	if (fp == nullptr)
	{
		//エラー
		return false;
	}


	wavHeader header;
	tagChank chank;
	wavFormat format;

	//ヘッダー読み込み
	fread(&header, sizeof(wavHeader), 1, fp);

	//チャンク読み込み
	fread(&chank, sizeof(chank), 1, fp);

	//フォーマット読み込み
	fread(&format, sizeof(wavFormat), 1, fp);

	unsigned int chankSize;
	fseek(fp, 4, SEEK_CUR);
	fread(&chankSize, sizeof(unsigned int), 1, fp);

	audiodata.resize(chankSize);

	fread(&audiodata[0], sizeof(unsigned short), audiodata.size(), fp);

	//ソースボイスの作成
	WAVEFORMATEX wavformat = {};

	wavformat.wFormatTag = WAVE_FORMAT_PCM;
	wavformat.nChannels = format.channels;
	wavformat.wBitsPerSample = format.bitsPerSample;
	wavformat.nSamplesPerSec = format.samplingRate;

	wavformat.nBlockAlign = wavformat.wBitsPerSample / 8 * wavformat.nChannels;
	wavformat.nAvgBytesPerSec = wavformat.nSamplesPerSec * wavformat.nBlockAlign;

	HRESULT hr = pXAudio2->CreateSourceVoice(&pSourceVoice, &wavformat);

	//サウンドバッファの作成
	XAUDIO2_BUFFER audiobuffer = {};
	audiobuffer.Flags = XAUDIO2_END_OF_STREAM;
	audiobuffer.AudioBytes = audiodata.size();
	audiobuffer.pAudioData = (BYTE*)&audiodata[0];

	hr = pSourceVoice->SubmitSourceBuffer(&audiobuffer);

	fclose(fp);

	return true;
}

void
XAudio::Load(const std::string& filePath)
{
	int extIdx = filePath.rfind('.');
	std::string ext = filePath.substr(extIdx + 1, filePath.length() - extIdx);

	if (ext == "wav" || ext == "WAV")
	{
		WavRead(filePath);
	}
	else if (ext == "mp3" || ext == "MP3")
	{
		MP3Read(filePath);
	}
}

void
XAudio::Terminate()
{
	if (pXAudio2)
	{
		pXAudio2->Release();
	}
	CoUninitialize();

}
#include "ReadMP3.h"
#include <Windows.h>
#include <mmreg.h>
#include <msacm.h>

// ビットレートのテーブル
const WORD bitRateTable[][16] =
{
	// MPEG1, Layer1
	{ 0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,-1 },
	// MPEG1, Layer2
	{ 0,32,48,56,64,80,96,112,128,160,192,224,256,320,384,-1 },
	// MPEG1, Layer3
	{ 0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,-1 },
	// MPEG2/2.5, Layer1,2
	{ 0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,-1 },
	// MPEG2/2.5, Layer3
	{ 0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,-1 }
};

// サンプリングレートのテーブル
const WORD sampleRateTable[][4] =
{
	{ 44100, 48000, 32000, -1 }, // MPEG1
	{ 22050, 24000, 16000, -1 }, // MPEG2
	{ 11025, 12000, 8000, -1 } // MPEG2.5
};

ReadMP3::ReadMP3()
{
}


ReadMP3::~ReadMP3()
{
}

bool
ReadMP3::Read(const std::string& filePath)
{
	FILE* fp = fopen(filePath.c_str(), "rb");

	if (fp == nullptr)
	{
		//エラー
		return false;
	}

	BYTE header[10];
	int offset = 0;
	int fileSize = 0;
	int size = 0;

	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	fread(&header[0], sizeof(BYTE), 10, fp);

	//先頭3バイトのチェック
	if (memcmp(header, "ID3", 3) == 0)
	{
		//タグサイズを取得
		DWORD tagSize =
			((header[6] << 21) |
			(header[7] << 14) |
				(header[8] << 7) |
				(header[9])) + 10;

		//データの位置、サイズを計算
		offset = tagSize;
		size = fileSize - offset;
	}
	else
	{
		//末尾のタグに移動
		BYTE tag[3];
		fseek(fp, fileSize - 128, SEEK_SET);
		fread(&tag[0], sizeof(BYTE), 3, fp);

		//データの位置、サイズを計算
		if (memcmp(tag, "TAG", 3) == 0)
		{
			size = fileSize - 128;	//末尾を省く
		}
		else
		{
			size = fileSize;		//ファイル全体がMP3データ
		}
	}

	//ファイルポインタをMP3データの開始位置に移動
	fseek(fp, offset, SEEK_SET);

	BYTE frameH[4];

	fread(&frameH, sizeof(BYTE), 4, fp);

	//同期ビットのチェック
	if (!(frameH[0] == 0xff && (frameH[1] & 0xe0) == 0xe0))
	{
		return false;
	}

	BYTE version = (frameH[1] >> 3) & 0x03;
	BYTE layer = (frameH[1] >> 1) & 0x03;


	int index;

	if (version == 3)
	{
		index = 3 - layer;
	}
	else
	{
		if (layer == 3)
		{
			index = 3;
		}
		else
		{
			index = 4;
		}
	}

	WORD bitRate = bitRateTable[index][frameH[2] >> 4];

	switch (version)
	{
	case 0:
		index = 2;
		break;
	case 2:
		index = 1;
		break;
	case 3:
		index = 0;
		break;
	}

	WORD sampleRate = sampleRateTable[index][(frameH[2] >> 2) & 0x03];

	BYTE padding = frameH[2] >> 1 & 0x01;
	BYTE channel = frameH[3] >> 6;

	WORD blockSize = ((144 * bitRate * 1000) / sampleRate) + padding;

	//フォーマット取得
	MPEGLAYER3WAVEFORMAT mf;
	mf.wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
	mf.wfx.nChannels = channel == 3 ? 1 : 2;
	mf.wfx.nSamplesPerSec = sampleRate;
	mf.wfx.nAvgBytesPerSec = (bitRate * 1000) / 8;
	mf.wfx.nBlockAlign = 1;
	mf.wfx.wBitsPerSample = 0;
	mf.wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;

	mf.wID = MPEGLAYER3_ID_MPEG;
	mf.fdwFlags =
		padding ?
		MPEGLAYER3_FLAG_PADDING_ON :
		MPEGLAYER3_FLAG_PADDING_OFF;
	mf.nBlockSize = blockSize;
	mf.nFramesPerBlock = 1;
	mf.nCodecDelay = 1393;

	//MP3からWAVWにデコードする
	WAVEFORMATEX wf;
	MMRESULT result;

	wf.wFormatTag = WAVE_FORMAT_PCM;
	result = acmFormatSuggest(
		nullptr,
		&mf.wfx,
		&wf,
		sizeof(WAVEFORMATEX),
		ACM_FORMATSUGGESTF_WFORMATTAG
	);

	if (result != MMSYSERR_NOERROR)
	{
		return false;
	}

	//wavFormat移行
	wavFormat.wFormatTag = wf.wFormatTag;
	wavFormat.nChannels = wf.nChannels;
	wavFormat.nSamplesPerSec = wf.nSamplesPerSec;
	wavFormat.nAvgBytesPerSec = wf.nAvgBytesPerSec;
	wavFormat.nBlockAlign = wf.nBlockAlign;
	wavFormat.wBitsPerSample = wf.wBitsPerSample;
	wavFormat.cbSize = wf.cbSize;


	HACMSTREAM has;
	result = acmStreamOpen(&has, nullptr, &mf.wfx, &wf, nullptr, 0, 0, ACM_STREAMOPENF_NONREALTIME);

	if (result != MMSYSERR_NOERROR)
	{
		return false;
	}

	DWORD mp3BlockSize = blockSize;
	DWORD waveBlockSize;
	result = acmStreamSize(
		has,
		mp3BlockSize,
		&waveBlockSize,
		ACM_STREAMSIZEF_SOURCE
	);

	if (result != MMSYSERR_NOERROR)
	{
		return false;
	}

	ACMSTREAMHEADER ash = {};
	ash.cbStruct = sizeof(ACMSTREAMHEADER);
	ash.pbSrc = new BYTE[mp3BlockSize];
	ash.cbSrcLength = mp3BlockSize;
	ash.pbDst = new BYTE[waveBlockSize];
	ash.cbDstLength = waveBlockSize;

	result = acmStreamPrepareHeader(has, &ash, 0);

	fread(ash.pbSrc, sizeof(BYTE), ash.cbSrcLength, fp);

	result = acmStreamConvert(has, &ash, ACM_STREAMCONVERTF_BLOCKALIGN | ACM_STREAMCONVERTF_START);


	if (result != MMSYSERR_NOERROR)
	{
		return false;
	}

	DWORD bufSize = size;
	DWORD bufRead = 0;
	DWORD pos = 0;
	DWORD readSize;

	while (size - pos >= mp3BlockSize)
	{
		long tmp = ftell(fp);
		if (tmp >= fileSize)
		{
			break;
		}
		fread(ash.pbSrc, sizeof(BYTE),ash.cbSrcLength - 4, fp);

		result = acmStreamConvert(has, &ash, ACM_STREAMCONVERTF_BLOCKALIGN | ACM_STREAMCONVERTF_START);

		readSize = ftell(fp) - tmp;
		pos += readSize;

		if (ash.cbDstLengthUsed == 0)
		{
			//デコード失敗
			MessageBox(nullptr, "変換に失敗しました。", nullptr, MB_ICONWARNING);
			return false;
		}

		//_buffer.push_back(ash.pbDst);

		//if (bufSize - bufRead > ash.cbDstLengthUsed)
		//{
		//	CopyMemory(_data + bufRead,
		//		ash.pbDst,
		//		ash.cbDstLengthUsed);

		//	bufRead += ash.cbDstLengthUsed;
		//}
		//else
		//{
		//	CopyMemory(
		//		_data + bufRead,
		//		ash.pbDst,
		//		bufSize - bufRead
		//	);
		//	bufRead += bufSize - bufRead;
		//	break;
		//}

		fread(&frameH, sizeof(BYTE), 4, fp);
	}


	// ACMの後始末
	acmStreamUnprepareHeader(has, &ash, 0);
	acmStreamClose(has, 0);

	fclose(fp);

	delete[] ash.pbSrc;
	delete[] ash.pbDst;

	return true;
}

bool 
ReadMP3::ReadTest(const std::string& filePath)
{
	// ファイルを開く
	HANDLE hFile = CreateFile(
		filePath.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE; // エラー

					  // ファイルサイズ取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	BYTE header[10];
	DWORD readSize;

	// ヘッダの読み込み
	ReadFile(hFile, header, 10, &readSize, NULL);

	DWORD offset; // MP3データの位置
	DWORD size; // MP3データのサイズ

				// 先頭３バイトのチェック
	if (memcmp(header, "ID3", 3) == 0) {
		// タグサイズを取得
		DWORD tagSize =
			((header[6] << 21) |
			(header[7] << 14) |
				(header[8] << 7) |
				(header[9])) + 10;

		// データの位置、サイズを計算
		offset = tagSize;
		size = fileSize - offset;
	}
	else {
		// 末尾のタグに移動
		BYTE tag[3];
		SetFilePointer(hFile, fileSize - 128, nullptr, FILE_BEGIN);
		ReadFile(hFile, tag, 3, &readSize, NULL);

		// データの位置、サイズを計算
		offset = 0;
		if (memcmp(tag, "TAG", 3) == 0)
			size = fileSize - 128; // 末尾のタグを省く
		else
			size = fileSize; // ファイル全体がMP3データ
	}

	// ファイルポインタをMP3データの開始位置に移動
	SetFilePointer(hFile, offset, nullptr, FILE_BEGIN);

	BYTE frameH[4];

	ReadFile(hFile, frameH, 4, &readSize, NULL);

	//同期ビットのチェック
	if (!(frameH[0] == 0xff && (frameH[1] & 0xe0) == 0xe0))
	{
		return false;
	}

	BYTE version = (frameH[1] >> 3) & 0x03;

	BYTE layer = (frameH[1] >> 1) & 0x03;

	INT index;
	if (version == 3) {
		index = 3 - layer;
	}
	else {
		if (layer == 3)
			index = 3;
		else
			index = 4;
	}

	WORD bitRate = bitRateTable[index][frameH[2] >> 4];

	switch (version) {
	case 0:
		index = 2;
		break;
	case 2:
		index = 1;
		break;
	case 3:
		index = 0;
		break;
	}
	WORD sampleRate =
		sampleRateTable[index][(frameH[2] >> 2) & 0x03];

	BYTE padding = frameH[2] >> 1 & 0x01;
	BYTE channel = frameH[3] >> 6;
	// サイズ取得
	WORD blockSize = ((144 * bitRate * 1000) / sampleRate) + padding;

	// フォーマット取得
	MPEGLAYER3WAVEFORMAT mf;
	mf.wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
	mf.wfx.nChannels = channel == 3 ? 1 : 2;
	mf.wfx.nSamplesPerSec = sampleRate;
	mf.wfx.nAvgBytesPerSec = (bitRate * 1000) / 8;
	mf.wfx.nBlockAlign = 1;
	mf.wfx.wBitsPerSample = 0;
	mf.wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;

	mf.wID = MPEGLAYER3_ID_MPEG;
	mf.fdwFlags =
		padding ?
		MPEGLAYER3_FLAG_PADDING_ON :
		MPEGLAYER3_FLAG_PADDING_OFF;
	mf.nBlockSize = blockSize;
	mf.nFramesPerBlock = 1;
	mf.nCodecDelay = 1393;

	WAVEFORMATEX wf;

	wf.wFormatTag = WAVE_FORMAT_PCM;
	acmFormatSuggest(
		NULL,
		&mf.wfx,
		&wf,
		sizeof(WAVEFORMATEX),
		ACM_FORMATSUGGESTF_WFORMATTAG
	);

	HACMSTREAM has;
	acmStreamOpen(&has, NULL, &mf.wfx, &wf, NULL, 0, 0, 0);

	DWORD mp3BlockSize = blockSize;
	DWORD waveBlockSize;
	acmStreamSize(
		has,
		mp3BlockSize,
		&waveBlockSize,
		ACM_STREAMSIZEF_SOURCE
	);

	ACMSTREAMHEADER ash = { 0 };
	ash.cbStruct = sizeof(ACMSTREAMHEADER);
	ash.pbSrc = new BYTE[mp3BlockSize];
	ash.cbSrcLength = mp3BlockSize;
	ash.pbDst = new BYTE[waveBlockSize];
	ash.cbDstLength = waveBlockSize;

	ReadFile(hFile, ash.pbSrc, ash.cbSrcLength - 4, &readSize, NULL);
	acmStreamConvert(has, &ash, ACM_STREAMCONVERTF_BLOCKALIGN);

	LPBYTE pBuffer;
	DWORD bufSize = size;
	DWORD bufRead;
	DWORD pos = 0;

	while (size - pos >= mp3BlockSize) { // MP3データの終端？
										 // １ブロック分だけMP3データを読み込む
		ReadFile(hFile, ash.pbSrc, ash.cbSrcLength, &readSize, NULL);
		pos += readSize;

		if (bufSize - bufRead > ash.cbDstLengthUsed) {
			// WAVEデータを格納するバッファに余裕があれば、
			// デコードしたWAVEデータをそのまま格納
			CopyMemory(
				pBuffer + bufRead,
				ash.pbDst,
				ash.cbDstLengthUsed
			);
			bufRead += ash.cbDstLengthUsed;
		}
		else {
			// WAVEデータを格納するバッファに余裕がなければ、
			// バッファの残り分だけデータを書き込む
			CopyMemory(
				pBuffer + bufRead,
				ash.pbDst,
				bufSize - bufRead
			);
			bufRead += bufSize - bufRead;
			break;
		}
	}

	return true;
}

WavForMp3 
ReadMP3::GetWavFormat()
{
	return wavFormat;
}

std::vector<unsigned char>& 
ReadMP3::GetBuffer()
{
	return _buffer;
}

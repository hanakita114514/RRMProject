#pragma once

#include <string>
#include <map>
#include <vector>
#include "ReadMP3.h"

class XAudio
{
private:

	//wav形式
	struct wavHeader
	{
		char riff[4];				//RIFFヘッダ
		unsigned int fileSize;		//ファイルサイズ
		char wave[4];				//WAVEヘッダ
	};

	struct tagChank
	{
		unsigned char fmt[4];		//fmtチャンク
		int fmtSize;				//fmtチャンクのバイト数
	};
	struct wavFormat
	{
		unsigned short id;			//フォーマットID
		unsigned short channels;	//チャンネル数
		unsigned int samplingRate;	//サンプリングレート
		unsigned int bytesPerSec;	//データ速度(Byte/sec)
		unsigned short blockSize;	//ブロックサイズ
		unsigned short bitsPerSample;//サンプルあたりのビット数
	};

	//mp3形式
	struct ID3v1Header
	{
		unsigned char headerID[3];		//ヘッダID
		unsigned char title[30];		//曲名
		unsigned char artist[30];		//アーティスト名
		unsigned char album[30];		//アルバム名
		unsigned char year[4];			//昨年年
		unsigned char comment[30];		//コメント
		unsigned char ganres;			//ジャンル
	};

	//FRAMEHEADER構造体
	typedef struct FrameHeader
	{
		int version;    //MPEGバージョン番号
		int layer;      //レイヤー番号
		int bitRate;    //ビットレート
		int sampleRate; //周波数
		int padding;    //パディングバイトの有無
		int channel;    //チャンネル数
		int frameSize;  //フレームサイズ
	};

private:

	XAudio();
	XAudio(const XAudio&);
	XAudio& operator=(const XAudio&);

	bool MP3Read(const std::string& filePath);
	bool WavRead(const std::string& filePath);

	ReadMP3 readMp3;

public:
	~XAudio();
	static XAudio& Instance()
	{
		static XAudio instance;

		return instance;
	}

	void Init();
	void Play();
	void Load(const std::string& filePath);
	void Terminate();

};


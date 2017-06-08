#pragma once
#include <dshow.h>

#include <map>

class MediaPlayer
{
private:
	IGraphBuilder* pGraphBuilder;
	IMediaControl* pMediaControl;
	IMediaPosition*	pMediaPosition;	//再生位置を指定するのに使う。

	BSTR _filePath;

public:
	MediaPlayer(BSTR filePath);
	~MediaPlayer();

	//初期化
	bool Init();
	//再生
	void Play();

	//再生中の場合でも先頭に戻して再生し直す
	void PlayFromStart();

	//一時停止
	void Pause();
	//音を止める(再生位置を最初に戻す)
	void Stop();

	//音量を変える
	//最小0 最大10000
	void SetVolume(long vol);
	//現在の音量を取得
	//最小0 最大10000
	long GetVolume();

	//終了処理
	void Terminate();
};


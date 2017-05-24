#pragma once

#include <map>
#include "MediaPlayer.h"

class MediaControl
{
private:
	MediaControl();
	MediaControl(const MediaControl&);
	MediaControl& operator = (const MediaControl&);

	std::map<BSTR, MediaPlayer*> _mediaMap;

public:
	~MediaControl();

	static MediaControl& Instance()
	{
		static MediaControl instance;

		return instance;
	}

	//ファイル読み込み
	int Load(BSTR filePath);
	//再生
	void Play(int handle);

	//再生中の場合でも先頭に戻して再生し直す
	void PlayFromStart(int handle);

	//一時停止
	void Pause(int handle);

	//音を止める(再生位置を最初に戻す)
	void Stop(int handle);

	//音量を変える
	//最小0 最大10000
	void SetVolume(long vol, int handle);

	//現在の音量を取得
	//最小0 最大10000
	long GetVolume(int handle);

	void Terminate();
};


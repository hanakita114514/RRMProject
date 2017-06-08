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

	//�t�@�C���ǂݍ���
	int Load(BSTR filePath);
	//�Đ�
	void Play(int handle);

	//�Đ����̏ꍇ�ł��擪�ɖ߂��čĐ�������
	void PlayFromStart(int handle);

	//�ꎞ��~
	void Pause(int handle);

	//�����~�߂�(�Đ��ʒu���ŏ��ɖ߂�)
	void Stop(int handle);

	//���ʂ�ς���
	//�ŏ�0 �ő�10000
	void SetVolume(long vol, int handle);

	//���݂̉��ʂ��擾
	//�ŏ�0 �ő�10000
	long GetVolume(int handle);

	void Terminate();
};


#pragma once
#include <dshow.h>

#include <map>

class MediaPlayer
{
private:
	IGraphBuilder* pGraphBuilder;
	IMediaControl* pMediaControl;
	IMediaPosition*	pMediaPosition;	//�Đ��ʒu���w�肷��̂Ɏg���B

	BSTR _filePath;

public:
	MediaPlayer(BSTR filePath);
	~MediaPlayer();

	//������
	bool Init();
	//�Đ�
	void Play();

	//�Đ����̏ꍇ�ł��擪�ɖ߂��čĐ�������
	void PlayFromStart();

	//�ꎞ��~
	void Pause();
	//�����~�߂�(�Đ��ʒu���ŏ��ɖ߂�)
	void Stop();

	//���ʂ�ς���
	//�ŏ�0 �ő�10000
	void SetVolume(long vol);
	//���݂̉��ʂ��擾
	//�ŏ�0 �ő�10000
	long GetVolume();

	//�I������
	void Terminate();
};


#pragma once

#include <string>
#include <map>
#include <vector>
#include "ReadMP3.h"

class XAudio
{
private:

	//wav�`��
	struct wavHeader
	{
		char riff[4];				//RIFF�w�b�_
		unsigned int fileSize;		//�t�@�C���T�C�Y
		char wave[4];				//WAVE�w�b�_
	};

	struct tagChank
	{
		unsigned char fmt[4];		//fmt�`�����N
		int fmtSize;				//fmt�`�����N�̃o�C�g��
	};
	struct wavFormat
	{
		unsigned short id;			//�t�H�[�}�b�gID
		unsigned short channels;	//�`�����l����
		unsigned int samplingRate;	//�T���v�����O���[�g
		unsigned int bytesPerSec;	//�f�[�^���x(Byte/sec)
		unsigned short blockSize;	//�u���b�N�T�C�Y
		unsigned short bitsPerSample;//�T���v��������̃r�b�g��
	};

	//mp3�`��
	struct ID3v1Header
	{
		unsigned char headerID[3];		//�w�b�_ID
		unsigned char title[30];		//�Ȗ�
		unsigned char artist[30];		//�A�[�e�B�X�g��
		unsigned char album[30];		//�A���o����
		unsigned char year[4];			//��N�N
		unsigned char comment[30];		//�R�����g
		unsigned char ganres;			//�W������
	};

	//FRAMEHEADER�\����
	typedef struct FrameHeader
	{
		int version;    //MPEG�o�[�W�����ԍ�
		int layer;      //���C���[�ԍ�
		int bitRate;    //�r�b�g���[�g
		int sampleRate; //���g��
		int padding;    //�p�f�B���O�o�C�g�̗L��
		int channel;    //�`�����l����
		int frameSize;  //�t���[���T�C�Y
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


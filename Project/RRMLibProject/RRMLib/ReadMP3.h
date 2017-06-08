#pragma once

#include <string>
#include <vector>

struct WavForMp3
{
	unsigned short  wFormatTag;
	unsigned short  nChannels;
	unsigned long  nSamplesPerSec;
	unsigned long nAvgBytesPerSec;
	unsigned short  nBlockAlign;
	unsigned short  wBitsPerSample;
	unsigned short  cbSize;
};


class ReadMP3
{
private:
	std::vector<unsigned char> _buffer;
	unsigned char* _data;
	WavForMp3 wavFormat;
public:
	ReadMP3();
	~ReadMP3();

	bool Read(const std::string& filePath);
	bool ReadTest(const std::string& filePath);

	WavForMp3 GetWavFormat();
	std::vector<unsigned char>& GetBuffer();
};


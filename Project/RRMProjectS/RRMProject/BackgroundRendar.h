#pragma once
class BackgroundRendar
{
private:
	int _bgImage;
	const char* _filePath;				//�摜�t�@�C���̃p�X

public:
	BackgroundRendar();
	~BackgroundRendar();

	bool Initialize(const char* imageFilePath);
	void Draw();					//�`��
};


#pragma once
class BackgroundRendar
{
private:
	int _bgImage;
	const char* _filePath;				//�摜�t�@�C���̃p�X

public:
	BackgroundRendar(const char* imageFilePath);
	~BackgroundRendar();

	bool Initialize();
	void Draw();					//�`��
};


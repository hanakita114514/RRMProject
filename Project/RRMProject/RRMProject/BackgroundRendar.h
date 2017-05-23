#pragma once
class BackgroundRendar
{
private:
	int _bgImage;
	const char* _filePath;				//画像ファイルのパス

public:
	BackgroundRendar(const char* imageFilePath);
	~BackgroundRendar();

	bool Initialize();
	void Draw();					//描画
};


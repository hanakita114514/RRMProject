#pragma once
class BackgroundRendar
{
private:
	int _bgImage;
	const char* _filePath;				//画像ファイルのパス

public:
	BackgroundRendar();
	~BackgroundRendar();

	bool Initialize(const char* imageFilePath);
	void Draw();					//描画
};


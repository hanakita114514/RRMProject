#pragma once

//キャラのステータスを表示する
class StatusUI
{
private:
	int _handle;

public:
	StatusUI();
	~StatusUI();

	void Draw();
};


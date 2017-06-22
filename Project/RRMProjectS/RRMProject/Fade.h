#pragma once

enum class FadeImage
{
	black,
	white,
	max
};

class Fade
{
private:

	Fade();
	Fade(const Fade &Inst);
	Fade & operator = (const Fade &Inst);

	bool _isFadeInEnd;
	bool _isFadeOutEnd;
	bool _isWait;
	bool _isPause;

	//int _handle;
	int _handle[(int)FadeImage::max];
	float _fadeSpeed;
	float _alpha;

	int _handleIdx;

	void (Fade::*_func)();

	void FadeIn();
	void FadeOut();
	void Wait();
	void Pause();

public:
	~Fade();

	static Fade& Instance()
	{
		static Fade instance;
		return instance;
	}

	void Init();
	void Update();
	void Draw();

	//フェードインを行う
	// fadeSpeed フェードのスピードの設定
	void FadeIn(const float& fadeSpeed);
	//画像のハンドルを指定するタイプ
	//フェードアウトを行う
	// fadeSpeed フェードのスピードの設定
	void FadeOut(const float& fadeSpeed);

	void PauseIn(const float& alpha = 127);

	//0を指定すると黒いフィルター、1を指定すると白いフィルターでフェードする
	void PauseIn(int handleIdx, const float& alpha = 127);

	void PauseEnd();

	// フェードインが終わったか調べる
	bool IsFadeInEnd();

	// フェードアウトが終わったか調べる
	bool IsFadeOutEnd();

	//待ち状態か？
	bool IsWait();

	//ポーズ状態か？
	bool IsPause();
};


#pragma once

class Fade
{
private:

	Fade();
	Fade(const Fade &Inst);
	Fade & operator = (const Fade &Inst);

	bool _isFadeInEnd;
	bool _isFadeOutEnd;
	bool _isWait;

	int _handle;

	float _fadeSpeed;
	float _alpha;

	void (Fade::*_func)();

	void FadeIn();
	void FadeOut();
	void Wait();

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
	//フェードアウトを行う
	// fadeSpeed フェードのスピードの設定
	void FadeOut(const float& fadeSpeed);


	// フェードインが終わったか調べる
	bool IsFadeInEnd();

	// フェードアウトが終わったか調べる
	bool IsFadeOutEnd();

	//待ち状態か？
	bool IsWait();
};


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
	bool _isPause;

	int _handle;

	float _fadeSpeed;
	float _alpha;

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

	//�t�F�[�h�C�����s��
	// fadeSpeed �t�F�[�h�̃X�s�[�h�̐ݒ�
	void FadeIn(const float& fadeSpeed);
	//�t�F�[�h�A�E�g���s��
	// fadeSpeed �t�F�[�h�̃X�s�[�h�̐ݒ�
	void FadeOut(const float& fadeSpeed);

	void PauseIn(const float& alpha = 127);

	void PauseEnd();

	// �t�F�[�h�C�����I����������ׂ�
	bool IsFadeInEnd();

	// �t�F�[�h�A�E�g���I����������ׂ�
	bool IsFadeOutEnd();

	//�҂���Ԃ��H
	bool IsWait();

	//�|�[�Y��Ԃ��H
	bool IsPause();
};


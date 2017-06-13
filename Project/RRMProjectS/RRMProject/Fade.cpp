#include "Fade.h"
#include <DxLib.h>


Fade::Fade()
{
	_fadeSpeed = 0;
	_func = &Fade::Wait;
}


Fade::~Fade()
{
}


void 
Fade::Init()
{
	_alpha = 0;
	_fadeSpeed = 0;
	_func = &Fade::Wait;
	_handle = DxLib::LoadGraph("Resource/img/BackGround/Fade.png");
	_isWait = false;
	_isFadeInEnd = false;
	_isFadeOutEnd = false;
}

void
Fade::Wait()
{
	_isWait = true;
}

void 
Fade::FadeIn()
{
	_alpha += _fadeSpeed;
	if (_alpha >= 255)
	{
		_alpha = 255;
		_func = &Fade::Wait;
		_isFadeInEnd = true;
	}
}

void 
Fade::FadeOut()
{
	_alpha -= _fadeSpeed;
	if (_alpha <= 0)
	{
		_alpha = 0;
		_func = &Fade::Wait;
		_isFadeOutEnd = true;
	}
}

void 
Fade::Pause()
{
	_isPause = true;
}

void 
Fade::Update()
{
	(this->*_func)();
}

void 
Fade::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)_alpha);
	DrawGraph(0, 0, _handle, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void  
Fade::FadeIn(const float& fadeSpeed)
{
	_fadeSpeed = fadeSpeed;
	_func = &Fade::FadeIn;
	_isFadeOutEnd = false;
	_isFadeInEnd = false;

}
void 
Fade::FadeOut(const float& fadeSpeed)
{
	_fadeSpeed = fadeSpeed;
	_func = &Fade::FadeOut;
	_isFadeOutEnd = false;
	_isFadeInEnd = false;
}

void
Fade::PauseIn(const float& alpha)
{
	_func = &Fade::Pause;
	_alpha = alpha;
	_isFadeOutEnd = false;
	_isFadeInEnd = false;
	_isPause = false;
}

void
Fade::PauseEnd()
{
	_func = &Fade::Wait;
	_alpha = 0;
	_isPause = false;
}

bool 
Fade::IsFadeInEnd()
{
	return _isFadeInEnd;
}

bool 
Fade::IsFadeOutEnd()
{
	return _isFadeOutEnd;
}

bool
Fade::IsWait()
{
	return _isWait;
}

bool
Fade::IsPause()
{
	return _isPause;
}
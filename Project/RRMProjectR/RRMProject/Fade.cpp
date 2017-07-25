#include "Fade.h"
#include <RRMLib.h>

//const float Y_ExtendLimit = 350;
//const float X_ExtendLimit = 300;


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
	_alpha = 255;
	_fadeSpeed = 0;
	_func = &Fade::Wait;
	_handle[0] = RRMLib::LoadGraph("Resource/img/BackGround/Fade.png");
	_handle[1] = RRMLib::LoadGraph("Resource/img/BackGround/whiteFilter.png");
	_isWait = false;
	_isFadeInEnd = false;
	_isFadeOutEnd = false;
	_handleIdx = (int)FadeImage::black;
	_extendPos[0] = Vector2(640, 350);
	_extendPos[1] = Vector2(640, 370);

	_extendX = _extendY = 0;
	_speed = 1;
}

void
Fade::Wait()
{
	_isWait = true;
}

void 
Fade::FadeIn()
{
	_handleIdx = (int)FadeImage::black;
	_alpha += _fadeSpeed * _speed;
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
	_alpha -= _fadeSpeed * _speed;
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
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, (int)_alpha);
	switch (_handleIdx)
	{
	case (int)FadeImage::black:
	{
		RRMLib::DrawGraph(0, 0, _handle[_handleIdx], true);
	}
	break;
	case (int)FadeImage::white:
	{
		RRMLib::DrawExtendGraph(_extendPos[0].x - _extendX, _extendPos[0].y - _extendY,
					_extendPos[1].x + _extendX, _extendPos[1].y + _extendY, _handle[_handleIdx], true , false);
	}
	break;
	}
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);
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
Fade::PauseIn(int handleIdx,const float& alpha)
{
	_func = &Fade::Pause;
	_alpha = alpha;
	_isFadeOutEnd = false;
	_isFadeInEnd = false;
	_isPause = false;
	_handleIdx = handleIdx;
}


void
Fade::PauseEnd()
{
	_func = &Fade::Wait;
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

void
Fade::ChangeFadeSpeed(float speed)
{
	_speed = speed;
}
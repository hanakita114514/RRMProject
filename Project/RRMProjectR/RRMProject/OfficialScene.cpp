#include "OfficialScene.h"
#include "GameMain.h"
#include "TitleScene.h"
#include <RRMLib.h>
#include "common.h"
#include "Fade.h"
#include "SceneManager.h"
#include "InputFactory.h"

static const float LOGO_W = 512.0f;
static const float LOGO_H = 96.0f;

static const float FADE_SPEED = 2.0f;

OfficialScene::OfficialScene()
{
	_update[State::start] = &OfficialScene::StartUpdate;
	_update[State::middle] = &OfficialScene::MiddleUpdate;
	_update[State::end] = &OfficialScene::EndUpdate;
	_state = State::start;

	_logoHandle = RRMLib::LoadGraph("Resource/img/UI/Logo.PNG");

	Fade::Instance().FadeOut(FADE_SPEED);

	RRMLib::ChangeBackColor(255, 255, 255);

	_frame = 0;

	_input = InputFactory::Create(InputMode::pad, 0);
}


OfficialScene::~OfficialScene()
{
	delete _input;
}


void 
OfficialScene::StartUpdate()
{
	if (Fade::Instance().IsFadeOutEnd())
	{
		_state = State::middle;
		Fade::Instance().FadeIn(FADE_SPEED);
	}
}

void 
OfficialScene::MiddleUpdate()
{
	if (_frame >= 30)
	{
		_frame = 0;
		_state = State::end;
	}
	++_frame;
}
void 
OfficialScene::EndUpdate()
{
	if (Fade::Instance().IsFadeInEnd())
	{
		RRMLib::ChangeBackColor(0, 0, 0);
		SceneManager::Instance().ChangeScene(SceneType::menu);
		Fade::Instance().ChangeFadeSpeed(1.0f);
	}
}

bool OfficialScene::Update()
{
	_input->Update();
	if (_input->Start())
	{
		Fade::Instance().ChangeFadeSpeed(3.0f);
	}
	RRMLib::DrawExtendGraph(WINDOW_WIDTH / 2 - LOGO_W / 2, WINDOW_HEIGHT / 2 - LOGO_H / 2,
		WINDOW_WIDTH / 2 + LOGO_W / 2, WINDOW_HEIGHT / 2 + LOGO_H, _logoHandle);

	(this->*_update[_state])();

	return true;
}


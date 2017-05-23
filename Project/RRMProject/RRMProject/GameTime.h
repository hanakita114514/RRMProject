#pragma once
#include "Timer.h"

//�Q�[���S�̂̎��Ԃ��Ǘ�
class GameTime
{
private:
	GameTime();
	GameTime(GameTime&);
	GameTime& operator = (GameTime&);

	Timer _time;

	//�S�̂̎���
	float _timeScale;

	float _deltaTime;
public:
	~GameTime();

	static GameTime& Instance()
	{
		static GameTime instance;

		return instance;
	}

	//���Ԃ̌W����ύX
	//0.0f �` 1.0f�Ŏw��
	void SetTimeScale(float scale);
	const float& GetTimeScale();
	const float& GetDeltaTime();

	//���[�v�n�܂�ŏ��ɌĂ�
	void BeginUpdate();
	//���[�v�̏I���Ō�ɌĂ�
	void EndUpdate();
};


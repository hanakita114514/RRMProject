#pragma once
#include "Timer.h"
#include <map>
#include "Object.h"

struct TimeData
{
	bool isStartUp;		//�������̈�
	float timeScale;
	float stopTime;		//�~�܂鎞��
	bool isSlow;		//�X���[���[�V�������H
};

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

	//�L�������̎���
	std::map<Object*, TimeData> _timeScales;

public:
	~GameTime();

	static GameTime& Instance()
	{
		static GameTime instance;

		return instance;
	}

	//���Ԃ̌W����ύX
	//0.0f �` 2.0f�Ŏw��
	void SetTimeScale(float scale);
	void SetTimeScale(float scale, Object* other);

	const float& GetTimeScale();
	const float& GetTimeScale(Object* other);

	const float& GetDeltaTime();

	TimeData& GetTimeData(Object* other);
	std::map<Object*, TimeData>& GetTimeScaleList();

	//���[�v�n�܂�ŏ��ɌĂ�
	void BeginUpdate();
	//���[�v�̏I���Ō�ɌĂ�
	void EndUpdate();
};


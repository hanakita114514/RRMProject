#pragma once
#include "Timer.h"
#include <map>
#include "Object.h"

struct TimeData
{
	bool isStartUp;		//初期化の為
	float timeScale;
	float stopTime;		//止まる時間
	bool isSlow;		//スローモーションか？
};

//ゲーム全体の時間を管理
class GameTime
{
private:
	GameTime();
	GameTime(GameTime&);
	GameTime& operator = (GameTime&);

	Timer _time;

	//全体の時間
	float _timeScale;

	float _deltaTime;

	//キャラ事の時間
	std::map<Object*, TimeData> _timeScales;

public:
	~GameTime();

	static GameTime& Instance()
	{
		static GameTime instance;

		return instance;
	}

	//時間の係数を変更
	//0.0f 〜 2.0fで指定
	void SetTimeScale(float scale);
	void SetTimeScale(float scale, Object* other);

	const float& GetTimeScale();
	const float& GetTimeScale(Object* other);

	const float& GetDeltaTime();

	TimeData& GetTimeData(Object* other);
	std::map<Object*, TimeData>& GetTimeScaleList();

	//ループ始まる最初に呼ぶ
	void BeginUpdate();
	//ループの終わる最後に呼ぶ
	void EndUpdate();
};


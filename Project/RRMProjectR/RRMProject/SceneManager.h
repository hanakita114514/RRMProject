#pragma once
#include "Scene.h"
#include "KeyConfig.h"

enum class SceneType
{
	official,
	title,
	menu,
	game,
	result,
};

//シーンマネージャー
class SceneManager
{
private:
	SceneManager();
	SceneManager(const SceneManager&);
	SceneManager& operator = (const SceneManager&);

	Scene* _scene;
	KeyData _keyData;
	LogoIdx _logoState;

public:
	~SceneManager();

	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}

	void Update();
	void ChangeScene(SceneType type);
	void ChangeScene(Scene* scene);

	void KeyConfig(KeyData& keyData);
	void LogoState(LogoIdx logoState);
};


#pragma once

#include <map>


enum class SoundType
{
	title,
	stage1,
	stage2,
	stage3,
	bossBattle,
};

enum class SEType
{
	firstAttack,			//�U�����̂���
	secondAttack,			//�U�����̂�
	thirdAttack,			//�U�����̂���
	damage,					//�_���[�W
	player_dead,			//�v���C���[���S
	decision,				//����{�^��
	explosion,				//����
	jump,					//�W�����v
	select,					//�I��
	avoid,					//���
	shot,					//��ѓ���
};

class SoundManager
{
private:
	SoundManager();
	SoundManager(const SoundManager&);
	SoundManager& operator = (const SoundManager&);

	std::map<SoundType, int> _soundMap;
	std::map<SEType, int> _seMap;

public:
	~SoundManager();

	static SoundManager& Instance()
	{
		static SoundManager instance;

		return instance;
	}

	void Play(SoundType st);
	void Play(SEType se);

	void PlayFromStart(SoundType st);
	void PlayFromStart(SEType se);

	//�S���̋Ȃ��~�߂�
	void Stop();
};


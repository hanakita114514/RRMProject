#pragma once
#include "Effect.h"

class DownEffect : public Effect
{
private:
	//�߂�l �A�j���[�V�����t���[����Ԃ�
	//UV���擾����
	int AnimUV();

public:
	DownEffect(int handle, const Position& pos, const Vector2& size);
	~DownEffect();

	void Update();
	void Draw(const Vector2& offset);
};


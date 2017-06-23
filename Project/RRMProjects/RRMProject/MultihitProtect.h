#pragma once

#include "Object.h"
#include <map>

//�����蔻��̑��i�q�b�g��h���N���X
class MultihitProtect
{
private:
	std::map <Object*, bool> _hitMap;

public:
	MultihitProtect();
	~MultihitProtect();

	//���łɓ������Ă��邩�H
	bool IsAlreadyHit(Object* other) { return _hitMap[other]; }
	//�����������ɌĂ�
	void Hit(Object* other);
	
	//������������������
	void Clear();
};


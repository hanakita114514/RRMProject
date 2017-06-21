#pragma once

//�L�����ɃA�[�}�[����������
class Armor
{
private:
	float _endurance;
	float _enduranceMax;

	float _waitTime;

public:
	Armor(float endurance);
	~Armor();

	//�����񕜂�����ꍇ����Ă�
	void AutomaticRecovery();
	//�S��
	void Recovery();
	//�񕜒l���w��
	void Recovery(float recoval);
	//�_���[�W
	void Damage(float damage);

	//�A�[�}�[����ꂽ���H
	bool IsBroken();

};


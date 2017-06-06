#include "EnemyManager.h"
#include "EnemyFactory.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
	Delete();
}

void EnemyManager::Update()
{
	for (auto& e : _enemyList)
	{
		e->Update();
	}

	//�폜���[�v
	//�s�v�Ȃ��̍폜���[�v
	//SheardPointer�̎����̈׈ꎞ�R�����g��
	std::vector<Enemy*>::iterator it = _enemyList.begin();
	for (; it != _enemyList.end();)
	{
		if ((*it)->IsDead())
		{
			delete(*it);
			*it = nullptr;
			it = _enemyList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void EnemyManager::Draw(const Vector2& offset)
{
	for (auto& e : _enemyList)
	{
		e->Draw(offset);
	}
}

void 
EnemyManager::Create(const EnemyType& et, const Position& pos)
{
	Enemy* newEnemy = _fac.Create(et, pos);
	_enemyList.push_back(newEnemy);

}

void
EnemyManager::Delete()
{
	std::vector<Enemy*>::iterator itr;
	itr = _enemyList.begin();
	for (itr; itr != _enemyList.end();)
	{
		delete (*itr);
		*itr = nullptr;
		itr = _enemyList.erase(itr);
	}
}

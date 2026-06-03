#pragma once
#include "../Base/BaseObject.h"

class GameScene;

class Player;

class Enemy : public Base
{
public:
	Enemy() { Init(); }
	~Enemy() { Release(); }

	enum EnemyType
	{
		Skelton,
		Necromancer,
	};

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;

	void Damage(float damage);

	bool IsAlive() const { return m_aliveFlg; }

	void SetEnemyType(EnemyType type) { m_type = type; }

	std::shared_ptr<Player>mp_player;

private:

	void Release() {}

	//std::shared_ptr<GameScene>m_owner;

	std::shared_ptr<KdSquarePolygon>m_poly;
	EnemyType m_type = EnemyType::Necromancer;

	Math::Vector3 m_enemyMove;

	float m_anime = 0;

	float m_hitPoint = 100;
	bool hit = false;

};
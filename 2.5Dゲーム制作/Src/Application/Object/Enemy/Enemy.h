#pragma once

class GameScene;

class Player;

class Enemy : public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() { Release(); }

	//enum EnemyType
	//{
	//	Skelton1,
	//	Skelton2,
	//	Vampaire,
	//	Necromancer,
	//};

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;

	//攻撃可能関数
	void Attack();

	void Damage(float damage);

	bool IsAlive() const { return m_aliveFlg; }

	std::shared_ptr<Player>mp_player;

private:

	void Release() {}

	//EnemyType* m_type ;

	//std::shared_ptr<GameScene>m_owner;

	std::shared_ptr<KdSquarePolygon>m_poly;

	Math::Vector3 m_enemyMove;

	float m_anime = 0;

	float m_attackCnt = 0;
	bool m_attackFlg = true;

	float m_hitPoint = 100;
	bool hit = false;

};
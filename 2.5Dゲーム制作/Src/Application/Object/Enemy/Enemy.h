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

private:

	void Release() {}

	//EnemyType* m_type ;

	//std::shared_ptr<GameScene>m_owner;
	std::shared_ptr<Player>m_player;

	std::shared_ptr<KdSquarePolygon>m_poly;

	Math::Vector3 m_enemyMove;

	float m_anime = 0;
};
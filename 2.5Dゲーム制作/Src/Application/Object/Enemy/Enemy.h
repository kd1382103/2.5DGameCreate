#pragma once

class GameScene;
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

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()			override;

private:

	void Release() {}

	GameScene* m_owner = nullptr;

	//EnemyType* m_type ;

	std::shared_ptr<KdSquarePolygon>m_poly;

	float m_anime = 0;
};
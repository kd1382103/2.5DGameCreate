#pragma once

class GameScene;

class Enemy;

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;

	void Attack();
	void Damage(float damage);

	bool IsAlive() const { return m_aliveFlg; }

	std::shared_ptr<Enemy>mp_enemy;

private:

	void Release() {}

	GameScene* m_owner = nullptr;

	std::shared_ptr<KdSquarePolygon>m_poly;


	float m_hitPoint = 100;
	bool hit = false;

	float m_attackCnt = 0;
	bool m_attackFlg = true;

	float m_anime = 0;

};
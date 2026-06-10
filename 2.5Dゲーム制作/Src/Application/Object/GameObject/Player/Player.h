#pragma once
#include <Application/Object/Base/BaseObject.h>

//class GameScene;

class Enemy;
class Weapons;

class Player : public Base
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;
	void DrawSprite()					override;

	void Damage(float damage)			override;

	bool IsAlive() const { return m_aliveFlg; }


private:

	void Release() {}

	//GameScene* m_owner = nullptr;

	std::shared_ptr<KdSquarePolygon>	m_poly		= nullptr;

	std::shared_ptr<KdTexture>			m_hpPoly	= nullptr;
	std::weak_ptr<KdCamera>				m_wpCamera;

	std::shared_ptr<Weapons>			m_weapons = nullptr;

	Math::Vector3 m_dir;

	float m_hitPoint = 100;
	bool hit = false;

	float m_anime = 0;
	int m_run[8];

	float m_attackInterval = 0;
	const int m_attackCoolTime = 40;

};
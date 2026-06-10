#pragma once
#include <Application/Object/Base/BaseObject.h>

class GameScene;

class Player;

class Score;
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

	void Damage(float damage)			override;

	void ExpiredAnimation();


	bool IsAlive() const { return m_aliveFlg; }

	void SetEnemyType(EnemyType type) { m_type = type; }

	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }

private:

	void Release() {}

	//std::shared_ptr<GameScene>m_owner;
	std::weak_ptr<Player>m_player;
	std::shared_ptr<Score>m_spScore;
	std::shared_ptr<KdSquarePolygon>m_poly;
	EnemyType m_type = EnemyType::Skelton;

	float m_anime = 0;

	float m_hitPoint = 100;
	bool hit = false;

};
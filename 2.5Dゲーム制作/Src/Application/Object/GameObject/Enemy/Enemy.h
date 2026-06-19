#pragma once
#include <Application/Object/Base/BaseObject.h>

class Player;
class Score;

class Enemy : public Base
{
public:
	Enemy() {}
	~Enemy() override{ Release(); }

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

	void Damage(float damage,int attackType)			override;

	void ExpiredAnimation();


	bool IsAlive() const { return m_aliveFlg; }

	void SetEnemyType(EnemyType type) { m_type = type; }

	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }

	void SetScore(const std::shared_ptr<Score>&score) { m_spScore = score; }

	void SetTarget(const std::shared_ptr<KdGameObject> target) override
	{
		m_target = target;

		if (auto spPlayer = std::dynamic_pointer_cast<Player>(target))
		{
			m_player = spPlayer;
		}
	}
	Math::Vector3 CalcAvoidWallVector();
	Math::Vector3 CalcAvoidEnemyVector();
private:

	void Release() {}

	EnemyType m_type = EnemyType::Skelton;

	float m_hitPoint = 100;

	bool hit = false;
	bool m_outroFlg = false;

	float m_anime = 0.0f;

	std::shared_ptr<KdSquarePolygon>m_poly;

	std::shared_ptr<Score>m_spScore;

	std::weak_ptr<Player>m_player;
};
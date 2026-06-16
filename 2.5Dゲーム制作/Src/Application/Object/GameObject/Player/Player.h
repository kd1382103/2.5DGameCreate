#pragma once
#include <Application/Object/Base/BaseObject.h>

class GameScene;
class Enemy;
class Weapons;
class Timer;
class Player : public Base
{
public:

	// 方向種類
	enum DirType
	{
		Up = 1 << 0,	
		Down = 1 << 1,	
		Left = 1 << 2,	
		Right = 1 << 3,	
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int   start;	
		int   end;		
		float count;	// 現在のカウント数
		float speed;	// アニメーションの速度
	};


	Player() { Init(); }
	~Player() { Release(); }

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;
	void DrawSprite()					override;

	void Damage		(float damage)		override;
	void SetOwner	(const std::shared_ptr<GameScene>& owner) { m_gameOwner =owner;}
	void SetTime	(const	std::shared_ptr<Timer>& timer) { m_timer = timer; }

	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }


private:

	void ChangeAnimetion();

	void Release() {}

	std::weak_ptr<GameScene>			m_gameOwner;

	std::shared_ptr<KdSquarePolygon>	m_poly		= nullptr;

	std::shared_ptr<KdTexture>			m_hpPoly	= nullptr;
	std::weak_ptr<KdCamera>				m_wpCamera;

	std::shared_ptr<Weapons>			m_weapons	= nullptr;
	std::shared_ptr<Timer>				m_timer		= nullptr;

	AnimationInfo m_animeInfo = {};
	UINT m_dirType = 0;

	Math::Vector3 m_dir;

	float m_hitPoint = 100;
	bool hit = false;

	float m_anime = 0;
	int m_run[8];

	float m_attackInterval = 0;
	const int m_attackCoolTime = 40;

};
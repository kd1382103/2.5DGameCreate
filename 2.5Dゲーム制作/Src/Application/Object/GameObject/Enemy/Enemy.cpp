#include "Enemy.h"
#include <Application/Scene/SceneManager.h>

//追加
#include <Application/Object/GameObject/Player/Player.h>
#include<Application/Object/Score/Score.h>
void Enemy::Init()
{
	Base::Init();

	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);


	//タイプ別初期設定
	switch (m_type)
	{
	case Skelton:
		m_poly->SetMaterial("Asset/Textures/Object/Enemy/skeleton1.png");
		m_poly->SetScale(1.0f);
		m_poly->SetSplit(17, 5);
		m_hitPoint = 50;
		m_moveSpeed = 0.15f;
		break;

	case Necromancer:
		m_poly->SetMaterial("Asset/Textures/Object/Enemy/Necromancer.png");
		m_poly->SetScale(1.5f);
		m_poly->SetSplit(17, 7);
		m_hitPoint = 200;
		m_moveSpeed = 0.1f;
		break;
	}

	m_nowPos	= {};
	m_moveVec	= { 0,0,0 };
	m_movePow	= 0;
	m_score		= 0;

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();

	//敵同士
	m_pCollider->RegisterCollisionShape("EnemyCollision", m_poly, KdCollider::TypeBump);

	//武器との当たり判定
	m_pCollider->RegisterCollisionShape("WeaponsCollision", { 0,0.5,0 }, 0.2, KdCollider::TypeDamage);


}

void Enemy::Update()
{
	if (m_outroFlg)
	{
		ExpiredAnimation();
		return;
	}


	if (m_isExpired) return;

	switch (m_type)
	{
	case Skelton:
	{
		//アニメーション制御
		int run[5] = { 69,70,71,72,73 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.1f;
		if (m_anime >= 5)
		{
			m_anime = 0;
		}
	}
	break;

	case Necromancer:
	{
		//アニメーション制御
		int run[7] = { 0,1,2,3,4,5,6 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.1f;
		if (m_anime >= 7)
		{
			m_anime = 0;
		}
	}
	break;
	}

	//移動処理
	if (!m_isExpired)
	{
		Math::Vector3 targetPos;
		if (m_target.expired() == false)
		{
			targetPos = m_target.lock()->GetPos();
		}

		Math::Vector3 dir = targetPos - m_nowPos;
		
		// ★ 距離が小さければ停止（震え防止）
		float dist = dir.Length();
		if (dist < 0.5f)
		{
			dir = { 0,0,0 };
		}
		else
		{
			dir.y = 0;
			dir.Normalize();
			m_nowPos += dir * m_moveSpeed;
		};

		Math::Matrix ScaleMat = Math::Matrix::CreateScale(2);
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);

		m_mWorld = ScaleMat * transMat;
		
	}
}

void Enemy::PostUpdate()
{
	//	VS	ステージ
	{
		{
			float maxOverlap = 0;
			Math::Vector3 hitDir;

			KdCollider::SphereInfo sphere;

			sphere.m_sphere.Center = m_nowPos;
			sphere.m_sphere.Center.y += 0.5f;
			sphere.m_sphere.Radius = 0.5;
			sphere.m_type = KdCollider::TypeGround;
			//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

			std::list<KdCollider::CollisionResult>retSphereList;
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				obj->Intersects(sphere, &retSphereList);
			}
		
			for (auto& ret : retSphereList)
			{
				if (maxOverlap < ret.m_overlapDistance)
				{
					maxOverlap = ret.m_overlapDistance;
					hitDir = ret.m_hitDir;
					hit = true;
				}
			}

			if (hit)
			{
				//押し戻し処理
				m_nowPos += hitDir * maxOverlap;
			}
		}
	}

	//	VS	敵同士
	{
		float maxOverlap = 0;
		Math::Vector3 hitDir;

		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_nowPos;
		sphere.m_sphere.Center.y += 0.5f;
		sphere.m_sphere.Radius = 0.55;
		sphere.m_type = KdCollider::TypeBump;
		//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
		std::list<KdCollider::CollisionResult>retSphereList;

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj.get() == this) continue;
			if (!std::dynamic_pointer_cast<Enemy>(obj))continue;
			obj->Intersects(sphere, &retSphereList);
		}

		for (auto& ret : retSphereList)
		{
			if (maxOverlap < ret.m_overlapDistance)
			{
				maxOverlap = ret.m_overlapDistance;
				hitDir = ret.m_hitDir;
			}
		}

		if (maxOverlap > 0)
		{
			//押し戻し弱化
			float pushRate = 0.4f;
			hitDir.y = 0;
			hitDir.Normalize();

			m_nowPos += hitDir * maxOverlap * pushRate;
		}
	}

	//プレイヤー
	{
		float maxOverlap = 0;
		Math::Vector3 hitDir;
		hit = false;

		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_nowPos;
		sphere.m_sphere.Center.y += 0.5f;
		sphere.m_sphere.Radius = 0.5f;
		sphere.m_type = KdCollider::TypeBump;

		std::list<KdCollider::CollisionResult> retList;

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj.get() == this)continue;
			auto player = std::dynamic_pointer_cast<Player>(obj);
			if (!player) continue;

			obj->Intersects(sphere, &retList);

			if (!retList.empty())
			{
				player->Damage(0.05f);
			}
		}
	}
}

void Enemy::GenerateDepthMapFromLight()
{
	if (!m_isExpired)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}

void Enemy::DrawLit()
{
	if (!m_isExpired)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}


void Enemy::Damage(float damage)
{
	if (m_outroFlg)return;

	m_hitPoint -= damage;
	if (m_hitPoint <= 0)
	{
		m_hitPoint = 0;
		m_outroFlg = true;
		m_anime = 0;

		if (m_spScore)
		{
			m_spScore->SetScore(100);
		}
	}
}

void Enemy::ExpiredAnimation()
{
	switch (m_type)
	{
	case Skelton:
	{
		//アニメーション制御
		int expiredAnime[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

		m_poly->SetUVRect(expiredAnime[(int)m_anime]);

		m_anime += 0.2f;
		if (m_anime >= 16)
		{
			m_isExpired = true;
		}
	}
	break;

	case Necromancer:
	{
		//アニメーション制御
		int expiredAnime[10] = {108,109,110,111,112.113,114,115,116,117};

		m_poly->SetUVRect(expiredAnime[(int)m_anime]);

		m_anime += 0.15f;
		if (m_anime >= 10)
		{
			m_isExpired = true;
		}
	}
	break;
	}
}



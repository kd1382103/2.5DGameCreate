#include "Enemy.h"
#include <Application/Scene/SceneManager.h>
#include <Application/Object/Player/Player.h>
#include<Application/Object/Weapons/Weapons.h>

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
	m_aliveFlg	= true;

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();

	//敵同士
	m_pCollider->RegisterCollisionShape("EnemyCollision", m_poly, KdCollider::TypeBump);

	//武器との当たり判定
	m_pCollider->RegisterCollisionShape("WeaponsCollision", { 0,0.5,0 }, 0.2, KdCollider::TypeDamage);


}

void Enemy::Update()
{
	if (!m_aliveFlg) return;

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
	if (m_aliveFlg)
	{
		m_enemyMove = mp_player->GetPos() - m_nowPos;

		// ★ 距離が小さければ停止（震え防止）
		float dist = m_enemyMove.Length();
		if (dist < 0.5f)
		{
			m_enemyMove = { 0,0,0 };
		}
		else
		{
			m_enemyMove.Normalize();
			m_nowPos += m_enemyMove * m_moveSpeed;
		}

		Math::Matrix ScaleMat = Math::Matrix::CreateScale(2);
		//Math::Matrix RotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
		m_mWorld = ScaleMat * transMat;
	}
}

void Enemy::PostUpdate()
{
	//	VS	地面
	{
		float maxOverlap = 0;
		Math::Vector3 hitPos;

		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center		= m_nowPos;
		sphere.m_sphere.Center.y	+= 0.2f;
		sphere.m_sphere.Radius		= 0.2;
		sphere.m_type = KdCollider::TypeGround;
		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
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
				hitPos = ret.m_hitDir;
				hit = true;
			}
		}

		if (hit)
		{
			m_nowPos += hitPos * maxOverlap;
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
		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
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

	//	VS	武器
	{
		float maxOverlap = 0;
		Math::Vector3 hitDir;

		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_nowPos;
		sphere.m_sphere.Center.y += 0.3f;
		sphere.m_sphere.Radius = 0.35;
		sphere.m_type = KdCollider::TypeDamage;
		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius,kRedColor);
		std::list<KdCollider::CollisionResult>retSphereList;

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj.get() == this) continue;
			if (!std::dynamic_pointer_cast<Weapons>(obj))continue;
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
}

void Enemy::GenerateDepthMapFromLight()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}

void Enemy::DrawLit()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}


void Enemy::Damage(float damage)
{
	m_hitPoint -= damage;
	if (m_hitPoint <= 0)
	{
		m_hitPoint = 0;
		m_aliveFlg = false;

		////死亡時のアニメーション後に呼び出す
		//m_isExpired = true;
	}
}



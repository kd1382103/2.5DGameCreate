#include "Player.h"
#include <Application/Scene/SceneManager.h>
#include <Application/Object/Enemy/Enemy.h>
#include <Application/Object/Weapons/Weapons.h>

void Player::Init()
{
	Base::Init();

	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Player/Player.png");

	m_poly->SetScale(1.25f);

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(8, 16);

	m_pCollider = std::make_unique<KdCollider>();

	m_pCollider->RegisterCollisionShape("PlayerCollision", m_poly, KdCollider::TypeBump);

	m_nowPos = {};
	m_moveVec = {};
	m_moveSpeed = 0.3f;
	m_movePow = 1.0f;
	m_aliveFlg = true;
}

void Player::Update()
{
	//アニメーション制御
	{
		int run[8] = { 0,1,2,3,4,5,6,7 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.05f;
		if (m_anime >= 8)
		{
			m_anime = 0;
		}
	}

	//移動処理
	{
		if (m_aliveFlg)
		{
			if (GetAsyncKeyState('D') & 0x8000)
			{
			}
			if (GetAsyncKeyState('A') & 0x8000)
			{	
			}
			if (GetAsyncKeyState('W') & 0x8000)
			{
			}
			if (GetAsyncKeyState('S') & 0x8000)
			{
			}
		}
	}

	//攻撃処理（オート）
	{
		mp_weapon = std::make_shared<Weapons>();
		mp_weapon->SetPos(m_nowPos);
		SceneManager::Instance().AddObject(mp_weapon);
	}

	Math::Matrix ScaleMat = Math::Matrix::CreateScale(2);
	//Math::Matrix RotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = ScaleMat * transMat;

}

void Player::PostUpdate()
{
	// //// //// //// //// ////
	//	 スフィア（球）判定  //
	// //// //// //// //// ////

	//ステージ
	{
		float maxOverlap = 0;
		Math::Vector3 hitDir;

		//球判定用変用意
		KdCollider::SphereInfo sphere;

		//球の中心座標設定
		sphere.m_sphere.Center = m_nowPos;
		//位置調整
		sphere.m_sphere.Center.y += 0.5f;

		//球の半径設定
		sphere.m_sphere.Radius = 0.5;

		//当たり判定をしたいタイプ設定
		sphere.m_type = KdCollider::TypeGround;

		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

		//球に当たったオブジェクト情報格納
		std::list<KdCollider::CollisionResult>retSphereList;

		//全てのオブジェクト当たり判定
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(sphere, &retSphereList);
		}

		for (auto& ret : retSphereList)
		{
			//球にめり込んだ長さが一番長いものを探す
			if (maxOverlap < ret.m_overlapDistance)
			{
				//更新
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

	//敵
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
			if (std::dynamic_pointer_cast<Enemy>(obj)) continue;
			obj->Intersects(sphere, &retList);
		}

		for (auto& ret : retList)
		{
			hit = true;
			if (maxOverlap < ret.m_overlapDistance)
			{
				maxOverlap = ret.m_overlapDistance;
				hitDir = ret.m_hitDir;
			}
		}

		if (hit)
		{
			//重ならないようにする（今回は重なるように作るので不要（見本として残す））
			
			//hitDir.y = 0;          // 上下揺れ防止
			//float pushRate = 0.4f; // 減衰でブルブル防止
			//m_nowPos += hitDir * maxOverlap * pushRate;

			Damage(0.05f);
		}
	}
}

void Player::GenerateDepthMapFromLight()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}
void Player::DrawLit()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}



void Player::Damage(float damage)
{
	m_hitPoint -= damage; 
	if (m_hitPoint <= 0) 
	{
		m_hitPoint = 0;
		m_aliveFlg = false; 
	}
}



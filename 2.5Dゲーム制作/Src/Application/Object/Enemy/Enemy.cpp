#include "Enemy.h"
#include "../../Scene/SceneManager.h"
#include "../Player/Player.h"


void Enemy::Init()
{
	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Enemy/skeleton1.png");

	m_poly->SetScale(0.4f);

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(17,5);

	//複数生成確認用
	//ランダムで生成位置を決定（のちに削除予定）
	float x = KdRandom::GetFloat(-30, 30);
	float z = KdRandom::GetFloat(-30, 30);
	
	m_nowPos	= {x,0,z};

	//m_nowPos	= {5,0,5};
	m_moveVec	= { 0,0,0 };
	m_moveSpeed = 0.1f;
	m_movePow	= 0;
	m_aliveFlg	= true;

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollision", m_poly, KdCollider::TypeBump);
}

void Enemy::Update()
{
	m_attackCnt--;
	if (m_attackCnt <= 0)
	{
		m_attackFlg = true;
		m_attackCnt = 50;
	}

	//アニメーション制御
	{
		int run[5] = { 69,70,71,72,73 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.1f;
		if (m_anime >= 5)
		{
			m_anime = 0;
		}
	}

	//攻撃処理
	if (m_attackFlg)
	{
		//Attack();
	}

	//移動処理
	if (m_aliveFlg)
	{
		//敵とプレイヤーの座標が等しくなければプレイヤーに向かって歩く
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
	//// //// //// //// //// ////
	//	 スフィア（球）判定    //
	//// //// //// //// //// ////

	{
		float maxOverlap = 0;
		Math::Vector3 hitDir;

		//球判定用変用意
		KdCollider::SphereInfo sphere;

		//球の中心座標設定
		sphere.m_sphere.Center = m_nowPos;
		//位置調整
		sphere.m_sphere.Center.y += 0.2f;

		//球の半径設定
		sphere.m_sphere.Radius = 0.2;

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
			//挙動確認（プレイヤーとの当たり判定が出来次第そちらに移動）
			//Attack();

			//押し戻し処理
			m_nowPos += hitDir * maxOverlap;
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

//攻撃処理
void Enemy::Attack()
{
	//アニメーション制御
	{
		int run[] = { 35,36,37,38,39,40,41,42,43 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.05f;
		if (m_anime >= 9)
		{
			m_anime = 0;
		}
	}

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		auto player = std::dynamic_pointer_cast<Player>(obj);

		// Playerかつ、死んでいない場合以外は無視
		if (!player) continue;
		if (!player->IsAlive()) continue;

		// 攻撃処理
		float dist = (player->GetPos() - m_nowPos).Length();
		if (dist < 1.0f)                 // 攻撃範囲
		{
			player->Damage(0.025f);
		}
	}
}

void Enemy::Damage(float damage)
{
	m_hitPoint -= damage;
	if (m_hitPoint <= 0)
	{
		m_hitPoint = 0;
		m_aliveFlg = false;
	}
}



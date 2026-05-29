#include "Player.h"
#include "../../Scene/SceneManager.h"

void Player::Init()
{
	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Player/idle.png");

	m_poly->SetScale(1.0f);

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(8, 4);

	m_nowPos = {};
	m_moveVec = {};
	m_moveSpeed = 0.3f;
	m_movePow = 0;
	m_aliveFlg = true;

	//Math::Matrix ScaleMat = Math::Matrix::CreateScale(2,2,2);
	//Math::Matrix RotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	//m_mWorld = ScaleMat * RotationX;

}

void Player::Update()
{
	//アニメーション制御
	{
		int run[8] = { 0,1,2,3,4,5,6,7 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.2f;
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
				m_nowPos.x += m_moveSpeed;
			}
			if (GetAsyncKeyState('A') & 0x8000)
			{
				m_nowPos.x -= m_moveSpeed;
			}
			if (GetAsyncKeyState('W') & 0x8000)
			{
				m_nowPos.z += m_moveSpeed;
			}
			if (GetAsyncKeyState('S') & 0x8000)
			{
				m_nowPos.z -= m_moveSpeed;
			}
		}
	}
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = transMat;

}

void Player::PostUpdate()
{
	// //// //// //// //// ////
	//	 スフィア（球）判定  //
	// //// //// //// //// ////

	float maxOverlap = 0;
	bool hit = false;
	Math::Vector3 hitDir;

	//球判定用変用意
	KdCollider::SphereInfo sphere;

	//球の中心座標設定
	sphere.m_sphere.Center = m_nowPos;
	//位置調整
	sphere.m_sphere.Center.y += 0.5f;

	//球の半径設定
	sphere.m_sphere.Radius = 0.4;

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

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly,m_mWorld);
}



#include "Enemy.h"
#include "../../Scene/SceneManager.h"
#include "../Player/Player.h"


void Enemy::Init()
{
	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Enemy/skeleton1.png");

	m_poly->SetScale(1.0f);

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(17,5);

	m_nowPos	= {};
	m_moveVec	= { 0,0,0 };
	m_moveSpeed = 0.1f;
	m_movePow	= 0;
	m_aliveFlg	= true;

	//Math::Matrix ScaleMat = Math::Matrix::CreateScale(1, 1, 1);
	//Math::Matrix RotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	//m_mWorld = ScaleMat * RotationX;

}

void Enemy::Update()
{
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

	//移動処理
	if (m_aliveFlg)
	{
		//敵とプレイヤーの座標が等しくなければプレイヤーに向かって歩く

		m_enemyMove = m_player->GetPos() - m_nowPos;
		m_enemyMove.Normalize();
		m_nowPos += m_enemyMove;

		Math::Matrix transMat	=	Math::Matrix::CreateTranslation(m_nowPos);
		m_mWorld =  transMat;
	}


	
}

void Enemy::PostUpdate()
{
	//// //// //// //// //// ////
//	 スフィア（球）判定    //
//// //// //// //// //// ////

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

void Enemy::GenerateDepthMapFromLight()
{

}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly,m_mWorld);
}



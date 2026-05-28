#include "Enemy.h"
#include "../Player/Player.h"

void Enemy::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Enemy/skeleton1/enemies-skeleton1_idle.png");

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(6,1);

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
		int run[11] = { 0,1,2,3,4,5,4,3,2,1,0 };

		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.1f;
		if (m_anime >= 11)
		{
			m_anime = 0;
		}
	}

	//移動処理
	if (m_aliveFlg)
	{
		//敵とプレイヤーの座標が等しくなければプレイヤーに向かって歩く

		Math::Matrix transMat	=	Math::Matrix::CreateTranslation(m_nowPos);
		m_mWorld =  transMat;
	}
}

void Enemy::PostUpdate()
{

}

void Enemy::GenerateDepthMapFromLight()
{

}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly,m_mWorld);
}



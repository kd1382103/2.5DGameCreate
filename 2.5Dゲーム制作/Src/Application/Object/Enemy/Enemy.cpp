#include "Enemy.h"

void Enemy::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Enemy/skeleton1/enemies-skeleton1_idle.png");

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(1,6);

	m_nowPos	= { 0,0,0 };
	m_moveVec	= { 0,0,0 };
	m_moveSpeed = 0;
	m_movePow	= 0;
	m_aliveFlg	= true;

	Math::Matrix ScaleMat = Math::Matrix::CreateScale(1, 1, 1);
	Math::Matrix RotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	m_mWorld = ScaleMat * RotationX;

}

void Enemy::Update()
{
	//アニメーション制御
	{
		m_anime += 0.15f;
		if (m_anime >= 17)
		{
			m_anime = 0;
		}
	}

	//移動処理
	if (m_aliveFlg)
	{
		//static float _yAng = 0;
		//Math::Matrix RotationY	=	Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
		//_yAng += 1.0f;
		Math::Matrix transMat		=	Math::Matrix::CreateTranslation(m_nowPos);
		m_mWorld = m_mWorld * transMat;
	}
}

void Enemy::PostUpdate()
{

}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly,m_mWorld);
}



#include "Player.h"

void Player::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Player/idle.png");

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
}

void Player::PostUpdate()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld =  transMat;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly,m_mWorld);
}



#include "Player.h"

void Player::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Player/IDLE/idel_down.png");

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_poly->SetSplit(1,8);

	m_nowPos	= { 0,0,0 };
	m_moveVec	= { 0,0,0 };
	m_moveSpeed = 0;
	m_movePow	= 0;
	m_aliveFlg	= true;

	Math::Matrix ScaleMat = Math::Matrix::CreateScale(1, 1, 1);
	Math::Matrix RotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//static float _yAng = 0;
		//Math::Matrix RotationY	=	Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
		//_yAng += 1.0f;
	m_mWorld = ScaleMat * RotationX;

}

void Player::Update()
{
	//アニメーション制御
	{
		int run[17] = {0,1,2,3,4,5,6,7,8,7,6,5,4,3,2,1,0};
		m_poly->SetUVRect(run[(int)m_anime]);

		m_anime += 0.15f;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	//移動処理
	if (m_aliveFlg)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_nowPos.x += 0.05f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_nowPos.x -= 0.05f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_nowPos.y += 0.05f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_nowPos.y -= 0.05f;
		}

		
		Math::Matrix transMat		=	Math::Matrix::CreateTranslation(m_nowPos);
		m_mWorld = m_mWorld * transMat;
	}
}

void Player::PostUpdate()
{

}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly,m_mWorld);
}



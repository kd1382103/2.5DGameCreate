#include "Player.h"

void Player::Update()
{
	m_moveSpeed = 0.25f;
	m_nowPos = m_player.Translation();

	m_moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVec.z += m_movePow;
	}
	if(GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVec.z -= m_movePow;
	}
	if(GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVec.x -= m_movePow;
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVec.x += m_movePow;
	}
	//正規化(あらゆる矢印の長さを「1.0」にする)
	m_moveVec.Normalize();
	m_nowPos += m_moveVec * m_moveSpeed;

	//キャラクターの座標を求める
	m_player = Math::Matrix::CreateTranslation(m_nowPos);

}

void Player::Draw()
{
}

void Player::Init()
{
	m_nowPos = { 0.0f,0.0f };
	m_moveVec = { 0.0f,0.0f };
	m_moveSpeed = 0.0f;
	m_movePow = 0.25f;
	m_aliveFlg = true;
}

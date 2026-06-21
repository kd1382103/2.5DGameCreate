#include "Rock3.h"

void Rock3::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rock/BigRock/Rock3/BigRock_03.gltf");

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RockCollision", m_model, KdCollider::TypeRock);
}

void Rock3::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = scaleMat * transMat;
}

void Rock3::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

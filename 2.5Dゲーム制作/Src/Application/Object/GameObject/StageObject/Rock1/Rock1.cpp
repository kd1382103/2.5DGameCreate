#include "Rock1.h"

void Rock1::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rock/BigRock/Rock1/BigRock_01.gltf");

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RockCollision", m_model, KdCollider::TypeRock);
}

void Rock1::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = scaleMat * transMat;
}

void Rock1::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

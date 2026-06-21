#include "Rock2.h"

void Rock2::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rock/BigRock/Rock2/BigRock_02.gltf");

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RockCollision", m_model, KdCollider::TypeRock);
}

void Rock2::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = scaleMat * transMat;
}

void Rock2::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

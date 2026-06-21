#include "Rock.h"

void Rock::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rock/Rock1/Rock_01.gltf");

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RockCollision", m_model, KdCollider::TypeGround);
}

void Rock::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = scaleMat * transMat;
}

void Rock::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

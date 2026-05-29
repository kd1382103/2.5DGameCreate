#include "Stage.h"

void Stage::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Starg/Hollow_Remnant/Hollow_Remnat.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(3);
	m_mWorld = scaleMat;

	//レイ判定
	m_pCollider = std::make_unique<KdCollider>();

	//当たり判定
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeGround);
}

void Stage::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

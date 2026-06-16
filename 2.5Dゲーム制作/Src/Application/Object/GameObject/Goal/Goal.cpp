#include "Goal.h"

void Goal::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Chest/Treasure_Chest.gltf");

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("GoalCollision", m_model, KdCollider::TypeGoal);
}

void Goal::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(5);
	Math::Matrix rotationYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 180);
	m_mWorld = scaleMat * rotationYMat * transMat;
}

void Goal::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
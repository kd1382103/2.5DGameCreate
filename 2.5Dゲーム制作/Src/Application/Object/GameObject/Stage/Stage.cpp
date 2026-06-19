#include "Stage.h"

void Stage::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Starg/Hollow_Remnant/Hollow_Remnat.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(20);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0,0,0);
	m_mWorld = scaleMat * transMat;

	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);

	KdShaderManager::Instance().WorkAmbientController().
		SetheightFog({ 0,0,0.75 }, 0.0f, -5.0f, 0.25f);

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeGround);
}

void Stage::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

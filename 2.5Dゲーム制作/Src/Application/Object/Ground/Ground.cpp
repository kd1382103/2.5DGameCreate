#include "Ground.h"

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Hollow_Remnant_floor.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(20, 20, 20);
	m_mWorld = scaleMat;
}

void Ground::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

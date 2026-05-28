#include "Ground.h"

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Hollow_Remnant_floor.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(1,0,1);
	m_mWorld = scaleMat;
}

void Ground::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

#include "Fog.h"

void Fog::Init()
{
	Base::Init();
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Starg/fog/fogUV.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(20);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = scaleMat * transMat;

	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);

	//高さfog
	KdShaderManager::Instance().WorkAmbientController().
		SetheightFog({ 0,0,0.75 }, 0.0f, -5.0f, 0.25f);
}

void Fog::Update()
{}

void Fog::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}


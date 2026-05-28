#include "Background.h"

void Background::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Background/Game/wall/Hollow_Remnant.png");
	m_poly->SetScale(200.0f);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_mWorld = Math::Matrix::CreateTranslation(Math::Vector3(0.0f, 0.0f, 100.0f));
}

void Background::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

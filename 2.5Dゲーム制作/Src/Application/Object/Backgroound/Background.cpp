#include "Background.h"

void Background::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Object/Background/Game/wall/Hollow_Remnant.png");
	m_polygon.SetScale(200.0f);
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_mWorld = Math::Matrix::CreateTranslation(Math::Vector3(0.0f, 0.0f, 100.0f));
}

void Background::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

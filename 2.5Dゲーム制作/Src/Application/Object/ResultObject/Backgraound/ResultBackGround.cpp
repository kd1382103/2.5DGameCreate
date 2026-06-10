#include "ResultBackGround.h"

void ResultBackGround::Init()
{
	m_poly = std::make_shared<KdTexture>();
	m_poly->Load("Asset/Textures/Object/Background/Result/Result.png");
}

void ResultBackGround::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_poly, 0, 0);
}

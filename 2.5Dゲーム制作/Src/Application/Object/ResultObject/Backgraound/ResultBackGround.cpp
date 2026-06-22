#include "ResultBackGround.h"

void ResultBackGround::Init()
{
	m_poly = std::make_shared<KdTexture>();
	m_poly->Load("Asset/Textures/Object/Background/Result/Result.png");

	m_bottonPoly = std::make_shared<KdTexture>();
	m_bottonPoly->Load("Asset/Textures/Object/Background/Result/botton.png");
}

void ResultBackGround::Update()
{
	alpha += alphaCnt;
	if (alpha >= alphaMax)
	{
		alpha = alphaMax;
		alphaCnt *= -1;
	}
	if (alpha <= alphaMin)
	{
		alpha = alphaMin;
		alphaCnt *= -1;
	}
}

void ResultBackGround::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_poly, 0, 0);
	Math::Color color = { 1,1,1,alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bottonPoly, 0, -200, nullptr, &color);
}

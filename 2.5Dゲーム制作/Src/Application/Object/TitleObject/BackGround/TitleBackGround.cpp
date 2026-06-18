#include "TitleBackGround.h"

void TitleBackGround::Init()
{
	m_poly = std::make_shared<KdTexture>();
	m_poly->Load("Asset/Textures/Object/Background/Title/Title.png");

	m_bottonPoly = std::make_shared<KdTexture>();
	m_bottonPoly->Load("Asset/Textures/Object/Background/Title/botton.png");
}

void TitleBackGround::Update()
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

void TitleBackGround::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_poly, 0, 0);
	Math::Color color = { 1,1,1,alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bottonPoly, 0, -100,nullptr,&color);
}

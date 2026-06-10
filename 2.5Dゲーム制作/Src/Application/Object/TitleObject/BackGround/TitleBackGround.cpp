#include "TitleBackGround.h"

void TitleBackGround::Init()
{
	m_poly = std::make_shared<KdTexture>();
	m_poly->Load("Asset/Textures/Object/Background/Title/Title.png");
}

void TitleBackGround::DrawSprite()
{
	std::shared_ptr<KdCamera>m_camera = m_wpCamera.lock();
	if (m_camera)
	{
		Math::Vector3 _3DPos = GetPos();
		_3DPos.z = -5.0f;

		Math::Vector3 _2DPos = Math::Vector3::Zero;
		m_camera->ConvertWorldToScreenDetail(_3DPos, _2DPos);
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_poly, _2DPos.x, _2DPos.y);
	}
}

#pragma once
#include <Application/Object/Base/BaseObject.h>

class TitleBackGround :public Base
{
public:
	TitleBackGround() { Init(); }
	~TitleBackGround()	override { Release(); }

	void Init()			override;
	void DrawSprite()	override;

	void SetCamera(std::shared_ptr<KdCamera> camera)
	{
		m_wpCamera = camera;
	}

private:

	std::shared_ptr<KdTexture>	m_poly;
	std::weak_ptr<KdCamera>		m_wpCamera;

};
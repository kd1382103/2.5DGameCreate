#pragma once
#include <Application/Object/Base/BaseObject.h>

class ResultBackGround :public Base
{
public:
	ResultBackGround() { Init(); }
	~ResultBackGround()	override { Release(); }

	void Init()			override;
	void DrawSprite()	override;
private:

	std::shared_ptr<KdTexture>	m_poly;
};
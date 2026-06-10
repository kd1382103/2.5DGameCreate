#pragma once
#include <Application/Object/Base/BaseObject.h>

class TitleBackGround :public Base
{
public:
	TitleBackGround() { Init(); }
	~TitleBackGround()	override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;


private:

	std::shared_ptr<KdTexture>	m_poly;
	std::shared_ptr<KdTexture>	m_bottonPoly;

	//点滅
	float alpha = 0;	//α値
	float alphaCnt = 0.01f;	//α値用カウント
	float alphaMax = 1;	//最大
	float alphaMin = 0;	//最小

};
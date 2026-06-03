#pragma once

class Base :public KdGameObject
{
public:

	Base() { Init(); }
	~Base() override { Release(); }

	void Init()							override;
	void PreUpdate()					override;
	void Update()						override;
	void PostUpdate()					override;
	void PreDraw()						override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;
	void DrawUnLit()					override;

private:

};
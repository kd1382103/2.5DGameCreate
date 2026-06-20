#pragma once
#include<Application/Object/Base/BaseObject.h>

class Effect :public Base
{
public:
	Effect() { Init(); }
	~Effect() override { Release(); }

	void Init()		override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }

private:

};
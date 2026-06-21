#pragma once
#include <Application/Object/Base/BaseObject.h>

class Rock :public Base
{
public:
	Rock() {}
	~Rock()	override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawLit()		override;
	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }

private:

	std::shared_ptr<KdModelData>m_model;

};
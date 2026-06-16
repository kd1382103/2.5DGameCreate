#pragma once
#include <Application/Object/Base/BaseObject.h>

class Goal :public Base
{
public:
	Goal() { Init(); }
	~Goal()	override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawUnLit()		override;

private:

	std::shared_ptr<KdModelData>m_model;

};
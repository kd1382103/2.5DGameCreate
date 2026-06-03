#pragma once
#include "../Base/BaseObject.h"

class Stage :public Base
{
public:
	Stage() { Init(); }
	~Stage()	override { Release(); }

	void Init()			override;
	void DrawUnLit()		override;

private:

	std::shared_ptr<KdModelData>m_model;

};
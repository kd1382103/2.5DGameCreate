#pragma once
#include<Application/Object/Base/BaseObject.h>

class Fog : public Base
{
public:
	Fog() { Init(); }
	~Fog() 	override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawUnLit()	override;

private:

	std::shared_ptr<KdModelData>m_model;

};
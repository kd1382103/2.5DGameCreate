#pragma once
#include <Application/Object/Base/BaseObject.h>

class Weapons:public::Base
{
public:

	//武器タイプ
	enum WeaponType
	{
		Sword,			//剣
		UltimateSlash,	//大技 : 剣
	};

	Weapons(WeaponType type = Sword):m_type(type)	{ Init(); }
	~Weapons()	{ Release(); }

	void Init	()		override;
	void Update	()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }

private:

	void Release();

	std::shared_ptr<KdSquarePolygon>m_poly;

	WeaponType m_type = WeaponType::Sword;

	float m_anime = 0;
	
	int m_run[8];

};
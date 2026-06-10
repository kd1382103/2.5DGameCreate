#include "Weapons.h"

//追加インクルード
#include <Application/Scene/SceneManager.h>

void Weapons::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	Base::Init();

	switch (m_type)
	{
		case Sword:
		{
			m_poly = std::make_shared<KdSquarePolygon>();
			m_poly->SetMaterial("Asset/Textures/Object/AttackEffect/Sword/Slash1/color3/sprite.png");
			m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Middle);
			m_poly->SetSplit(5, 2);
			m_poly->SetScale(4.0f);
			m_nowPos = {};

			break;
		}
	}

}

void Weapons::Update()
{
	switch (m_type)
	{
		case Sword:
		{
			//アニメーション制御
			int attack[8] = { 0,1,2,3,4,5,6,7 };

			m_poly->SetUVRect(attack[(int)m_anime]);

			m_anime += 0.75f;
			if (m_anime >= 8) 
			{ 
				m_isExpired = true;
			}

			break;
		}
	}	

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = transMat;
}

void Weapons::PostUpdate()
{
	if (m_anime >= 2)
	{
		return;
	}

	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Radius = 0.5;
	sphere.m_type = KdCollider::TypeDamage;

	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, nullptr) == true)	
		{
			obj->Damage(10.0f);
		}
	}
}

void Weapons::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Weapons::Release()
{}

#include "Weapons.h"

//追加インクルード
#include <Application/Scene/SceneManager.h>

void Weapons::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	Base::Init();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("");

	//m_poly->SetScale();

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//m_poly->SetSplit(8, 16);

	m_nowPos = {};
}

void Weapons::Update()
{
	switch (m_type)
	{
		case Bleed:
		{
			//アニメーション制御
			//int attack[5] = { 69,70,71,72,73 };

			//m_poly->SetUVRect(attack[(int)m_anime]);

			//m_anime += 0.5f;
			//if (m_anime >= 5) 
			//{ 
			//	m_isExpired = true;
			//}

			break;
		}
	}	

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = transMat;
}

void Weapons::PostUpdate()
{
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Radius = 0.3;
	sphere.m_type = KdCollider::TypeDamage;

	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, nullptr) == true)	
		{
			obj->Damage(1.0f);
		}
	}

}

void Weapons::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Weapons::Release()
{}

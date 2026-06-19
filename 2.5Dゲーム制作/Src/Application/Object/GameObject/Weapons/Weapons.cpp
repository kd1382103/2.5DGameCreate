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
			m_poly->SetMaterial("Asset/Textures/Object/AttackEffect/Sword/sprite.png");
			m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
			m_poly->SetSplit(5, 2);
			m_poly->SetScale(4.0f);
			m_nowPos = {};

			break;
		}
		case UltimateSlash:
		{
			m_poly = std::make_shared<KdSquarePolygon>();
			m_poly->SetMaterial("Asset/Textures/Object/AttackEffect/Ultimet/sprite.png");
			m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
			m_poly->SetSplit(5, 2); // 24フレーム
			m_poly->SetScale(8.0f); // 画面全体
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
			int attack[8] = { 0,1,2,3,4,5,6,7 };

			m_poly->SetUVRect(attack[(int)m_anime]);

			m_anime += 0.75f;
			if (m_anime >= 8) 
			{ 
				m_isExpired = true;
			}

			break;
		}
		case UltimateSlash:
		{
			int attack[9] = { 0,1,2,3,4,5,6,7,8 };

			m_poly->SetUVRect(attack[(int)m_anime]);

			for (int i = 0;i < 5;++i)
			{
				m_anime += 0.2f;
				if (m_anime >= 9)
				{
					m_anime = 0;
					if (i >= 4)
					{
						m_isExpired = true;
					}
				}
			}
		}
	}	

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = transMat;
}

void Weapons::PostUpdate()
{
	switch (m_type)
	{
		case Sword:
		{
			if (m_anime >= 2) { return; }

			KdCollider::SphereInfo sphere;
			sphere.m_sphere.Center = GetPos();
			sphere.m_sphere.Radius = 0.8;
			sphere.m_type = KdCollider::TypeDamage;

			m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->Intersects(sphere, nullptr) == true)
				{
					obj->Damage(12.5f , 0);
				}
			}
			break;
		}

		case UltimateSlash:
		{
			if (m_anime > 7) return; // 多段ヒットは最初だけ

			KdCollider::SphereInfo sphere;
			sphere.m_sphere.Center = m_nowPos;
			sphere.m_sphere.Radius = 5.0f; // 広範囲
			sphere.m_type = KdCollider::TypeDamage;

			m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->Intersects(sphere, nullptr))
				{
					obj->Damage(10.0f , 1); // 多段ヒットなので1発は控えめ
				}
			}
		}
	}
}

void Weapons::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Weapons::Release()
{}

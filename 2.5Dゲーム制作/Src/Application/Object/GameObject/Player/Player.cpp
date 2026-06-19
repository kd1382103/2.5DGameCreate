#include "Player.h"
#include <Application/Scene/SceneManager.h>

//追加インクルード
#include <Application/Object/GameObject/Weapons/Weapons.h>
#include<Application/Object/Score/Score.h>
#include <Application/Scene/GameScene/GameScene.h>
#include <Application/Scene/ResultScene/ResultScene.h>
#include<Application/Object/Timer/Timer.h>

void Player::Init()
{
	Base::Init();

	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Object/Player/Player.png");
	m_poly->SetScale(1.5f);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_poly->SetSplit(8, 16);

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PlayerCollision", m_poly, KdCollider::TypeBump);

	m_animeInfo.start = 0;		// 開始コマ
	m_animeInfo.end = 7;		// 終了コマ
	m_animeInfo.count = 0;		// 現在のカウント数
	m_animeInfo.speed = 0.2f;	// アニメーションの速度

	m_nowPos = {};
	m_moveVec = {};
	m_dir = {};

	m_moveSpeed = 0.3f;
	m_movePow = 1.0f;

	m_attackInterval = 0;
	m_attackDir = {};
	m_aliveFlg = true;

	m_mWorld = Math::Matrix::Identity;

}

void Player::Update()
{
	if (m_outroFlg)
	{
		OutroUpdate();
		return;
	}

	//移動処理
	{
		UINT oldDirType = m_dirType;

		m_dir = {};
		m_dirType = 0;

		if (m_aliveFlg)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				m_dir.z += 1;		
				m_dirType |= DirType::Up;

			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				m_dir.z -= 1;		
				m_dirType |= DirType::Down;

			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				m_dir.x += 1;
				m_dirType |= DirType::Right;
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				m_dir.x -= 1;
				m_dirType |= DirType::Left;
			}

			if (m_dirType != oldDirType && m_dirType != 0)
			{
				ChangeAnimetion();

				m_attackDir = m_dir;
				m_attackDir.Normalize();

			}
			else
			{
				m_dirType = oldDirType;
			}

			m_dir.Normalize();
			m_nowPos += m_dir * m_moveSpeed;

			//アニメーション制御
			{
				m_animeInfo.count += m_animeInfo.speed;
				int animeCnt = static_cast<int>(m_animeInfo.start + m_animeInfo.count);

				if (animeCnt > m_animeInfo.end)
				{
					animeCnt = m_animeInfo.start;
					m_animeInfo.count = 0;
				}
				m_poly->SetUVRect(animeCnt);

			}
		}

		//攻撃処理
		{
			//クールタイム追加予定

			// 攻撃キーの現在状態
			//通常
			bool attackKeyNow = (GetAsyncKeyState(VK_SPACE) & 0x8000);
			bool attackKeyPressed = attackKeyNow && !m_keyFlg;

			//大技
			bool ultimateKeyNow = (GetAsyncKeyState('Z') & 0x8000);
			bool ultimateKeyPressed = ultimateKeyNow && !m_ultimateFlg;

			//大技発動条件
			bool canUltimate = (m_ultimateGauge >= m_ultimateMax);

			if (m_aliveFlg)
			{
				// 攻撃オブジェクトを出現させる座標を確定する
				//通常用
				Math::Vector3 attackPos = m_nowPos + m_attackDir * 1.5f;

				//大技用
				Math::Vector3 ultimatePos = m_nowPos + m_attackDir;

				// ★ 大技（Z）
				if (ultimateKeyPressed && m_ultimateGauge >= m_ultimateMax)
				{
					m_ultimateGauge = 0; // 消費
					
					m_weapons = std::make_shared<Weapons>(Weapons::UltimateSlash);
					m_weapons->SetPos(attackPos);
					SceneManager::Instance().AddObject(m_weapons);
					KdAudioManager::Instance().Play("Asset/Sounds/ULTAtttack.wav", false);
				}
			
				// ★ 通常攻撃（SPACE）
				if (attackKeyPressed)
				{
					m_weapons = std::make_shared<Weapons>(Weapons::Sword);
					m_weapons->SetPos(attackPos);
					SceneManager::Instance().AddObject(m_weapons);
					KdAudioManager::Instance().Play("Asset/Sounds/Attack.WAV", false);
				}
			}

			// 次のフレームのために保存
			m_keyFlg = attackKeyNow;
			m_ultimateFlg = ultimateKeyNow;
		}
	}

	Math::Matrix ScaleMat = Math::Matrix::CreateScale(2);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_nowPos);
	m_mWorld = ScaleMat * transMat;


	//デバック（プレイヤー即死）
	if (GetAsyncKeyState('1') & 0x8000)
	{
		Damage(100);
	}
}

void Player::PostUpdate()
{
	// //// //// //// //// ////
	//	 スフィア（球）判定  //
	// //// //// //// //// ////

	//ステージ
	{
		float maxOverlap = 0;
		Math::Vector3 hitDir;

		//球判定用変用意
		KdCollider::SphereInfo sphere;

		//球の中心座標設定
		sphere.m_sphere.Center = m_nowPos;
		//位置調整
		sphere.m_sphere.Center.y += 0.5f;

		//球の半径設定
		sphere.m_sphere.Radius = 0.5;

		//当たり判定をしたいタイプ設定
		sphere.m_type = KdCollider::TypeGround;

		//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

		//球に当たったオブジェクト情報格納
		std::list<KdCollider::CollisionResult>retSphereList;

		//全てのオブジェクト当たり判定
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(sphere, &retSphereList);
		}

		for (auto& ret : retSphereList)
		{
			//球にめり込んだ長さが一番長いものを探す
			if (maxOverlap < ret.m_overlapDistance)
			{
				//更新
				maxOverlap = ret.m_overlapDistance;
				hitDir = ret.m_hitDir;
				hit = true;
			}
		}

		if (hit)
		{
			//押し戻し処理
			m_nowPos += hitDir * maxOverlap;
		}
	}

	//ゴール
	{
		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_nowPos;
		sphere.m_sphere.Center.y += 0.5f;
		sphere.m_sphere.Radius = 0.5;

		sphere.m_sphere.Center = m_nowPos;
		sphere.m_sphere.Center.y += 0.5f;
		sphere.m_sphere.Radius = 0.5;
		sphere.m_type = KdCollider::TypeGoal;
		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
		std::list<KdCollider::CollisionResult>retSphereList;
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(sphere, &retSphereList);
		}

		if (!retSphereList.empty())
		{
			goalHit = true;
		}

		if (goalHit)
		{
			if (auto owner = m_gameOwner.lock())
			{
				SceneManager::Instance().m_finalScore = owner->GetScore()->GetScore();
				SceneManager::Instance().m_finalTime = m_timer->GetTime();
			}
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		}
	}
}

void Player::GenerateDepthMapFromLight()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}
void Player::DrawLit()
{
	if (m_outroFlg)
	{
		float range = 0.2;
		Math::Vector3 color = { 1,0.3,0.3 };
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve, &range, &color);
	}

	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}

void Player::DrawSprite()
{
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

	if (_spCamera)
	{
		// プレイヤーの頭上位置
		Math::Vector3	_3DPos		= GetPos();
		_3DPos.y += 2.5f;

		Math::Matrix	camWorld	= _spCamera->GetCameraMatrix();
		Math::Vector3	camRight	= camWorld.Right();

		_3DPos += camRight * 0.2f;

		// 3D → 2D 座標変換
		Math::Vector3 _2DPos = Math::Vector3::Zero;
		_spCamera->ConvertWorldToScreenDetail(_3DPos, _2DPos);

		// ゲージの基本サイズ
		float gaugeWidth = 80.0f;   // 横幅
		float gaugeHeight = 10.0f;  // 高さ

		// HP割合（0.0 ～ 1.0）
		//clamp -> 値を指定した範囲に収める（はみ出さないようにする）関数
		float hpRate = std::clamp(m_hitPoint / m_maxHitPoint,0.0f,1.0f);
		hpRate = std::clamp(hpRate, 0.0f, 1.0f);

		// 現在HPに応じた幅
		float currentWidth = gaugeWidth * hpRate;

		// DrawBox は extentX = 幅の半分
		float halfGaugeW = gaugeWidth * 0.5f;
		float halfCurrentW = currentWidth * 0.5f;

		float left = _2DPos.x - halfGaugeW;

		Math::Color color = { 0,0,0,1 };

		// 背景（黒枠）
		KdShaderManager::Instance().m_spriteShader.DrawBox
		(
			_2DPos.x,
			_2DPos.y,
			halfGaugeW,
			gaugeHeight * 0.5,
			&color
		);

		color = { 1,0,0,1 };
		float hpCenterX = left + currentWidth / 2;

		// HPゲージ本体（赤）
		KdShaderManager::Instance().m_spriteShader.DrawBox
		(
			hpCenterX,
			_2DPos.y,
			halfCurrentW,
			gaugeHeight * 0.5,
			&color
		);
	}
}

void Player::OutroUpdate()
{
	m_dissolve += 0.025;
	if (m_dissolve > 1)
	{
		m_aliveFlg = false;
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}
}

void Player::Damage(float damage)
{
	if (m_outroFlg || !m_aliveFlg) return;

	m_hitPoint -= damage;
	if (m_hitPoint <= 0)
	{
		m_hitPoint = 0;
		m_outroFlg = true;

		if (auto owner = m_gameOwner.lock())
		{
			SceneManager::Instance().m_finalScore = owner->GetScore()->GetScore();
			SceneManager::Instance().m_finalTime = m_timer->GetTime();
		}
	}
}

void Player::ChangeAnimetion()
{
	//上下左右
	if (m_dirType & DirType::Up)
	{
		m_animeInfo.start	= 56;
		m_animeInfo.end	= 63;
	}
	if (m_dirType & DirType::Down)
	{
		m_animeInfo.start	= 32;
		m_animeInfo.end	= 39;
	}
	if (m_dirType & DirType::Left)
	{
		m_animeInfo.start	= 40;
		m_animeInfo.end	= 47;
	}
	if (m_dirType & DirType::Right)
	{
		m_animeInfo.start	= 48;
		m_animeInfo.end	= 55;
	}
}
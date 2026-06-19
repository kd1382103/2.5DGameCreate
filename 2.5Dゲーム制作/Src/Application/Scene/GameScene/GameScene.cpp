#include "GameScene.h"
#include<Application/Scene/SceneManager.h>

#include  <Application/Object/GameObject/Stage/Stage.h>
#include  <Application/Object/GameObject/Goal/Goal.h>
#include  <Application/Object/GameObject/Fog/Fog.h>

#include<Application/Object/GameObject/Player/Player.h>
#include<Application/Object/GameObject/Enemy/Enemy.h>

#include<Application/Object/GameObject/SpawnArea/SpawnArea.h>

#include<Application/Object/GameObject/KeyUI/KeyUI.h>

#include<Application/Object/Score/Score.h>
#include<Application/Object/Timer/Timer.h>

void GameScene::Event()
{
	//高さfog
	KdShaderManager::Instance().WorkAmbientController().
		SetheightFog({ 0,0,0.75 }, 0.0f, -5.0f, 0.25f);

	if (!m_player->GetAlive())
	{
		return;
	}

	// ★ クリアしたら敵を全削除
	if (SceneManager::Instance().m_isClear)
	{
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (dynamic_cast<Enemy*>(obj.get()))
			{
				obj->SetAlive(false); // 消滅
			}
		}
	}

	//　カメラ処理
	{
		Math::Vector3 camPos = { 0,10,-10 };

		//上からの挙動確認用
		//Math::Vector3 camPos = { 0,20,0 };

		//横からの挙動確認用
		//Math::Vector3 camPos = { 0,3,-10 };

		//斜め上から斜め下に(メイン採用予定)
		//Math::Vector3 camPos = { -5,5,-5 };

		Math::Matrix rotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
		Math::Matrix rotationYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));

		Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());

		Math::Matrix camWorld = rotationXMat * transMat;
		//Math::Matrix camWorld = rotationXMat * rotationYMat * transMat;
		m_camera->SetCameraMatrix(camWorld);
	}

	
	//敵のスポーン
	{
		// ★ クリアしたら敵のスポーンを止める
		if (SceneManager::Instance().m_isClear)
		{
			return; // 敵スポーン処理を全部スキップ
		}

		int now = m_time->GetTime();   // Timer の秒数

		for (auto& sp : m_spawnAreas)
		{
			// まずタイマー更新
			sp->UpdateTimer(now, m_spawnInterval);

			// フラグが有効でなければスキップ
			if (!sp->CanSpawn())
				continue;

			// プレイヤーが範囲内にいなければスキップ
			if (!sp->IsPlayerInTrigger(m_player->GetPos()))
				continue;

			// 敵数チェック
			int enemyCount = 0;
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (dynamic_cast<Enemy*>(obj.get()))
					enemyCount++;
			}
			if (enemyCount >= 80)
				continue;

			// 敵の種類切り替え
			bool spawnNecromancer = ((now / 40) % 2) == 1;

			int count = sp->GetSpawnCount();
			for (int i = 0; i < count; i++)
			{
				m_enemy = std::make_shared<Enemy>();
				m_enemy->SetEnemyType(spawnNecromancer ? Enemy::Necromancer : Enemy::Skelton);

				//三項演算子 ? ->true なら「? の右側（左側の値）」,false なら「: の右側（右側の値）」
				//今回だとtrueならネクロマンサー、falseならスケルトンが出現

				m_enemy->Init();
				m_enemy->SetPos(sp->GetRandomPos());
				m_enemy->SetTarget(m_player);
				m_enemy->SetScore(m_score);
				AddObject(m_enemy);
			}

			// ★スポーンしたので、このスポーンエリアだけ時間リセット
			sp->ResetTimer(now, m_spawnInterval);
		}
	}

	//BGM（ループ）
	//KdAudioManager::Instance().Play("", true);
}

void GameScene::Init()
{
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	


	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	//ステージ
	m_stage = std::make_shared<Stage>();
	AddObject(m_stage);

	//ゴール
	m_goal = std::make_shared<Goal>();
	AddObject(m_goal);

	//霧
	m_fog = std::make_shared<Fog>();
	//AddObject(m_fog);

	//プレイヤー
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_player->SetPos({ 0,0,160 });
	m_player->SetAlive(true);
	m_player->SetOwner(shared_from_this());
	m_player->SetCamera(m_camera);
	AddObject(m_player);

	//スコア
	m_score = std::make_shared<Score>();
	m_score->SetScorePos({ -550,300 });
	AddObject(m_score);

	//敵の出現場所配置
	{
		int enemyNum = 10;
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 0,0,-150 });
			sp->SetRadius(3.0f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 0,0,140 });
			sp->SetRadius(3.0f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ -100,0,-75 });
			sp->SetRadius(4.0f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 100,0,-20 });
			sp->SetRadius(2.5f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 190,0,50 });
			sp->SetRadius(2.5f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}

		SpawnEnemies();
	}

	//タイマー
	m_time = std::make_shared<Timer>();
	m_time->SetTimePos({ 450,300 });
	m_time->SetPlayer(m_player);

	m_player->SetTime(m_time);

	AddObject(m_time);

	//キーUI
	m_KeyUI = std::make_shared<KeyUI>();
	m_KeyUI->SetTarget(m_player);
	AddObject(m_KeyUI);

	auto bg = std::make_shared<KdModelData>();
	bg->Load("Asset/Models/Stage/backgroundPlane.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(100);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, -10, 0);
	Math::Matrix world = scaleMat * transMat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*bg, world);

}

void GameScene::SpawnEnemies()
{
	for (auto& sp : m_spawnAreas)
	{
		//int count = KdRandom::GetInt(sp->GetMinSpawn(), sp->GetMaxSpawn());
		int count = sp->GetSpawnCount();

		for (int i = 0; i < count; i++)
		{
			m_enemy= std::make_shared<Enemy>();
			m_enemy->Init();
			m_enemy->SetPos(sp->GetRandomPos());
			m_enemy->SetTarget(m_player);
			m_enemy->SetScore(m_score);
			AddObject(m_enemy);
		}
	}
}
